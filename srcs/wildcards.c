#include "minishell.h"

char	*get_wild_ptr(t_shell *shell)
{
	int		i;
	char	*ptr;

	i = -1;
	ptr = &shell->cmd[0];
	while (++i <= shell->j)
	{
		ptr += (count_char(ptr, '\'') + count_char(ptr, '"'));
		ptr += count_char(ptr, ' ');
		ptr += (count_char(ptr, '\'') + count_char(ptr, '"'));
		ptr += ft_strlen(shell->words[i]);
	}
	return (ptr);
}

int	quotes_check(t_shell *shell)
{
	char	*ptr;
	int		i;
	int		qs[2];

	ptr = get_wild_ptr(shell);
	if (!ptr)
		return (0);
	qs[0] = 0;
	qs[1] = 0;
	i = 0;
	while ((ptr - shell->cmd - i) > 0)
	{
		if ((shell->cmd)[i] == '\'' && !qs[1])
			qs[0] += 1;
		else if ((shell->cmd)[i] == '"' && !qs[0])
			qs[1] += 1;
		i++;
	}
	if (qs[0] && qs[0] % 2 == 0)
		return (1);
	if (qs[1] && qs[1] % 2 == 0)
		return (2);
	return (1);
}

void	not_wild_sub(t_shell *shell, char **cmd, char **tmp)
{
	int	check;

	if (shell->j)
	{
		check = quotes_check(shell);
		if (check == 2)
			*cmd = ft_charjoin(*cmd, '\'');
		else if (check == 1)
			*cmd = ft_charjoin(*cmd, '"');
	}
	shell->i = -1;
	while ((*tmp)[++(shell->i)])
		*cmd = ft_charjoin(*cmd, (*tmp)[shell->i]);
	if (shell->j)
	{
		check = quotes_check(shell);
		if (check == 2)
			*cmd = ft_charjoin(*cmd, '\'');
		else if (check == 1)
			*cmd = ft_charjoin(*cmd, '"');
	}
}

void	wild_loop(char **cmd, t_shell *shell, char **tmp, char **new)
{
	while (shell->words[shell->j][++(shell->i)])
	{
		if (shell->words[shell->j][shell->i] == '*' && quotes_check(shell))
		{
			parse_wild(new, &shell->words[shell->j]);
			break ;
		}
		else
			*tmp = ft_charjoin(*tmp, shell->words[shell->j][shell->i]);
	}
	if (shell->words[shell->j][0] && shell->words[shell->j][shell->i] != '*')
		not_wild_sub(shell, cmd, tmp);
	else if (shell->words[shell->j][0])
	{
		shell->i = -1;
		while ((*new)[++(shell->i)])
			*cmd = ft_charjoin(*cmd, (*new)[shell->i]);
	}
}

void	replace_wild(char **cmd, t_shell *shell)
{
	char	*tmp;
	char	*new;

	shell->words = split_cmd(*cmd, count_quotes(*cmd), "\0");
	free(*cmd);
	shell->j = -1;
	*cmd = ft_strdup("");
	while (shell->words[++(shell->j)])
	{
		shell->i = -1;
		new = ft_strdup("");
		tmp = ft_strdup("");
		wild_loop(cmd, shell, &tmp, &new);
		*cmd = ft_charjoin(*cmd, ' ');
		free(tmp);
		free(new);
	}
	free_matrix(shell->words);
}
