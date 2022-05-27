#include "minishell.h"

int	count_char(char *cmd, char c)
{
	int	i;

	i = -1;
	while (cmd[++i])
		if (!(cmd[i] == c))
			break ;
	return (i);
}

int	count_word_len(char *cmd)
{
	int	i;
	int	quotes;
	int	double_quotes;

	i = -1;
	quotes = 0;
	double_quotes = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '\'' && !double_quotes)
			quotes = (quotes + 1) % 2;
		else if (cmd[i] == '"' && !quotes)
			double_quotes = (double_quotes + 1) % 2;
		if (!quotes && !double_quotes && (cmd[i] == ' '))
			break ;
	}
	return (i);
}

int	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	if (!ft_strncmp(cmd, "env", 4))
		return (1);
	if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	if (!ft_strncmp(cmd, "export", 7))
		return (1);
	if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	return (0);
}

void	copy_pipeline(char ***pieces, int *i, char *pipe_in)
{
	char	**tmp_pipe;
	int		j;

	if ((*pieces)[0] != NULL && pipe_in && !is_builtin((*pieces)[0]))
	{
		j = -1;
		tmp_pipe = ft_split(pipe_in, '\n');
		while (tmp_pipe[++j])
		{
			(*pieces)[(*i)++] = ft_strdup(tmp_pipe[j]);
		}
		free_matrix(tmp_pipe);
	}
	(*pieces)[*i] = NULL;
}

char	**split_cmd(char *cmd, int quotes, char *pipe_in)
{
	char	**pieces;
	int		i;
	int		j;
	int		word_len;

	i = 0;
	if (pipe_in)
		i = ft_strlen(pipe_in);
	pieces = malloc(sizeof(char *) * (quotes + 1));
	i = -1;
	j = 0;
	while (++i < quotes)
	{
		j += count_char(&cmd[j], ' ');
		word_len = count_word_len(&cmd[j]);
		if ((cmd[j] == '"' && cmd[j + word_len - 1] == '"')
			|| (cmd[j] == '\'' && cmd[j + word_len - 1] == '\''))
			pieces[i] = ft_strndup(&cmd[j + 1], word_len - 1);
		else
			pieces[i] = ft_strndup(&cmd[j], word_len + 1);
		j += word_len;
	}
	pieces[i] = NULL;
	return (pieces);
}
