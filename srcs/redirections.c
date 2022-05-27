#include "minishell.h"

// #####################  in redirections  #####################

int	process_in_file_mode(t_shell *shell)
{
	int	fd;

	fd = open(shell->words[0], O_RDONLY);
	free(shell->pipe);
	if (fd < 0)
	{
		ft_printf("\033[0;31m%s: No such file or directory\033[0m\n",
			shell->words[0]);
		shell->pipe = ft_strdup("");
	}
	free_matrix(shell->words);
	(shell->fix)++;
	if (fd < 0)
		return (1);
	get_pipe_exit(fd, shell);
	close(fd);
	return (0);
}

int	process_in_line_mode(t_shell *shell)
{
	char	*line;
	char	buffer;
	int		i;

	while (1)
	{
		line = malloc(sizeof(char) * 1);
		line[0] = '\0';
		write(1, "> ", 2);
		while (read(0, &buffer, 1) && buffer != 10)
			line = ft_charjoin(line, buffer);
		if (!line || !ft_strncmp(line, shell->words[0],
				ft_strlen(shell->words[0]) + 1))
			break ;
		i = -1;
		while (line[++i])
			shell->pipe = ft_charjoin(shell->pipe, line[i]);
		shell->pipe = ft_charjoin(shell->pipe, '\n');
		free(line);
	}
	(shell->fix)++;
	free(line);
	free_matrix(shell->words);
	return (0);
}

int	process_in_mode(t_shell *shell, int *i)
{
	int		quotes;

	if (ft_strchr("|>C&^(", shell->mode[shell->fix]))
		return (0);
	replace_env(&shell->cmd_list[*i + 1], shell);
	quotes = count_quotes(shell->cmd_list[*i + 1]);
	shell->words = split_cmd(shell->cmd_list[*i + 1], quotes, shell->pipe);
	if (shell->mode[shell->fix] == '<')
		return (process_in_file_mode(shell));
	if (shell->mode[shell->fix] == 'A')
		return (process_in_line_mode(shell));
	free_matrix(shell->words);
	return (0);
}

// #####################  out redirections  #####################

void	process_out_mode(t_shell *shell, int *i)
{
	int	fd;
	int	quotes;

	if ((shell->fix - 1) >= 0 && ft_strchr("<A", shell->mode[shell->fix - 1]))
		(*i)++;
	if (!shell->pipe || ft_strchr("|&^(", shell->mode[shell->fix]))
		return ;
	replace_env(&shell->cmd_list[*i + 1], shell);
	quotes = count_quotes(shell->cmd_list[*i + 1]);
	shell->words = split_cmd(shell->cmd_list[*i + 1], quotes, shell->pipe);
	if (shell->mode[shell->fix] == '>')
		fd = open(shell->words[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(shell->words[0], O_WRONLY | O_CREAT | O_APPEND, 0666);
	(shell->fix)++;
	(*i)++;
	free_matrix(shell->words);
	if (fd < 0)
		return ;
	write(fd, shell->pipe, ft_strlen(shell->pipe));
	close(fd);
	free(shell->exit_code);
	free(shell->pipe);
	shell->exit_code = ft_strdup("0");
	shell->pipe = ft_strdup("");
}
