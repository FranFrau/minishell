#include "minishell.h"

void	set_shlvl(char ***env, char **envp, int i)
{
	char	*shlvl;

	shlvl = ft_itoa(ft_atoi(&envp[i][6]) + 1);
	(*env)[i] = ft_strjoin("SHLVL=", shlvl);
	free(shlvl);
}

void	init_env(char **envp, char ***env)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	*env = malloc(sizeof(char *) * (i + 1));
	i = -1;
	if (!(*env))
		exit(write(1, "Error allocating env\n", 21));
	while (envp[++i])
	{
		if (!ft_strncmp("SHLVL=", envp[i], 6))
			set_shlvl(env, envp, i);
		else if (!ft_strncmp("SHELL=", envp[i], 6))
			(*env)[i] = ft_strdup("SHELL=minishell");
		else
		{
			(*env)[i] = ft_strdup(envp[i]);
			if ((*env)[i])
				continue ;
			free_matrix((*env));
			exit(write(1, "Error setting up env\n", 21));
		}
	}
	(*env)[i] = 0;
}

int	replace_env_var(char **cmd, char *path, t_shell *shell, int i)
{
	int	j;
	int	k;

	j = -1;
	while (ft_isalnum(path[i]))
		i++;
	if (path[1] == '?' && i--)
	{
		while (shell->exit_code[++j])
			*cmd = ft_charjoin(*cmd, shell->exit_code[j]);
		return (1);
	}
	while (shell->env[++j])
	{
		if (!ft_strncmp(shell->env[j], &path[1], i - 1)
			&& shell->env[j][i - 1] == '=')
		{
			k = 0;
			while (shell->env[j][i - 1 + ++k])
				*cmd = ft_charjoin(*cmd, shell->env[j][i - 1 + k]);
			break ;
		}
	}
	return (i - 1);
}

void	little_free(char **cmd, char *cmd_mod)
{
	free(*cmd);
	*cmd = ft_strdup(cmd_mod);
	free(cmd_mod);
}

void	replace_env(char **cmd, t_shell *shell)
{
	char	*cmd_mod;
	int		i;
	int		quotes[2];

	i = -1;
	quotes[0] = 0;
	quotes[1] = 0;
	cmd_mod = malloc(sizeof(char) * 2);
	if (!cmd_mod)
		return ;
	ft_bzero(cmd_mod, 2);
	while ((*cmd)[++i])
	{
		if ((*cmd)[i] == '\'' && !quotes[1])
			quotes[0] = (quotes[0] + 1) % 2;
		if ((*cmd)[i] == '\"')
			quotes[1] = (quotes[1] + 1) % 2;
		if ((*cmd)[i] == '$' && !quotes[0])
			i += replace_env_var(&cmd_mod, &(*cmd)[i], shell, 1);
		else
			cmd_mod = ft_charjoin(cmd_mod, (*cmd)[i]);
	}
	little_free(cmd, cmd_mod);
}
