#include "minishell.h"

// #####################  free  #####################

int	free_matrix(char **matrix)
{
	int	i;

	i = -1;
	if (!matrix)
		return (1);
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
	return (0);
}

void	free_shell(t_shell *shell, int mod)
{
	free_matrix(shell->env);
	free(shell->path);
	free(shell->exit_code);
	if (mod == 1)
	{
		free_matrix(shell->cmd_list);
		free(shell->mode);
		free(shell->cmd);
		free_matrix(shell->words);
	}
	else if (mod == 2)
		free(shell->pipe);
}

// #####################  readline  #####################

char	*get_line(int fd)
{
	char	buffer;
	char	*str;

	if (fd < 0)
		return (NULL);
	str = malloc(sizeof(char) * 1);
	str[0] = '\0';
	while (read(fd, &buffer, 1) && buffer != 10)
		str = ft_charjoin(str, buffer);
	if (buffer != 10)
	{
		free(str);
		write(1, "\n", 1);
		return (NULL);
	}
	return (str);
}

void	get_pipe_exit(int fd, t_shell *shell)
{
	char	buffer;

	if (fd < 0)
		return ;
	shell->pipe = malloc(sizeof(char) * 1);
	shell->pipe[0] = '\0';
	while (read(fd, &buffer, 1))
		shell->pipe = ft_charjoin(shell->pipe, buffer);
}

// #####################  get path  #####################

char	*get_path(char **env)
{
	char	*path;
	int		i;
	int		j;

	i = -1;
	path = malloc(sizeof(char) * 1);
	path[0] = '\0';
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
		{
			j = 3;
			while (env[i][++j])
				path = ft_charjoin(path, env[i][j]);
			break ;
		}
	}
	return (path);
}
