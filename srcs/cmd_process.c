#include "minishell.h"

char	*find_cmd_path(char *cmd, char **env, int i)
{
	char	**paths;
	char	*path;

	while (env[i] && !ft_strnstr(env[i], "PATH", 4))
		i++;
	if (!env[i])
		return (cmd);
	paths = ft_split(env[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_charjoin(paths[i], '/');
		path = ft_strjoin(paths[i], cmd);
		if (!access(path, F_OK))
		{
			free_matrix(paths);
			free(cmd);
			return (path);
		}
		free(path);
	}
	free_matrix(paths);
	return (cmd);
}

// #####################  cmd processing  #####################

int	count_quotes(char *cmd)
{
	int	i;
	int	count;
	int	double_quotes;
	int	quotes;

	i = -1;
	count = 0;
	double_quotes = 0;
	quotes = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '"' && !quotes)
			double_quotes = (double_quotes + 1) % 2;
		else if (cmd[i] == '\'' && !double_quotes)
			quotes = (quotes + 1) % 2;
		if ((!quotes && !double_quotes) && !(cmd[i] == ' ')
			&& ((cmd[i + 1] == ' ') || !cmd[i + 1]))
			count++;
	}
	return (count);
}

int	process_builtins(t_shell *shell)
{
	if (!ft_strncmp(shell->words[0], "echo", 5))
		echo(shell);
	else if (!ft_strncmp(shell->words[0], "env", 4))
		env(shell);
	else if (!ft_strncmp(shell->words[0], "cd", 3))
	{
		shell->pipe = ft_strdup("");
		free(shell->exit_code);
		shell->exit_code = ft_itoa(change_dir(shell));
	}
	else if (!ft_strncmp(shell->words[0], "export", 7))
		export(shell);
	else if (!ft_strncmp(shell->words[0], "unset", 6))
		unset(shell);
	else if (!ft_strncmp(shell->words[0], "pwd", 4))
		shell->pipe = ft_charjoin(ft_strdup(shell->path), '\n');
	else
		return (0);
	return (1);
}

int	process_programs(t_shell *shell)
{
	char	*tmp;

	if (!shell->words[0] || !shell->words[0][0])
		return (1);
	if (!ft_strncmp(shell->words[0], "exit", 5))
	{
		if (shell->mode[shell->fix] == '|' || (shell->fix > 0
				&& shell->mode[shell->fix - 1] == '|'))
			shell->pipe = ft_strdup("");
		return (0);
	}
	if (!process_builtins(shell))
	{
		tmp = find_cmd_path(ft_strdup(shell->words[0]), shell->env, 0);
		free(shell->words[0]);
		shell->words[0] = tmp;
		execute_pipe(shell);
		if (!ft_strncmp(shell->exit_code, "127", 4))
			ft_printf("\033[0;31m%s: command not found\033[0m\n",
				shell->words[0]);
	}
	return (0);
}

int	process_cmd(char **cmd, t_shell *shell)
{
	int		quotes_count;

	replace_env(cmd, shell);
	replace_wild(cmd, shell);
	quotes_count = count_quotes(*cmd);
	shell->words = split_cmd(*cmd, quotes_count, shell->pipe);
	if (shell->words[0]
		&& ft_strnstr(shell->words[0], "cat", ft_strlen(shell->words[0]))
		&& shell->fix && shell->mode[shell->fix - 1] == 'A')
		ft_printf("%s", shell->pipe);
	else
	{
		if (shell->pipe != NULL)
			free(shell->pipe);
		if (process_programs(shell))
			shell->pipe = ft_strdup("");
	}
	return (free_matrix(shell->words));
}
