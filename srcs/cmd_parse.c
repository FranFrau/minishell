#include "minishell.h"

int	count_cmd(char *cmd, int *pc)
{
	while (cmd[++pc[3]])
	{
		if (cmd[pc[3]] == '\'' && !pc[2])
			pc[1] = (pc[1] + 1) % 2;
		else if (cmd[pc[3]] == '"' && !pc[1])
			pc[2] = (pc[2] + 1) % 2;
		else if (cmd[pc[3]] == '(' && !pc[1] && !pc[2])
			pc[4]++;
		else if (cmd[pc[3]] == ')' && !pc[1] && !pc[2])
			pc[4]--;
		else if (ft_strchr("|<>", cmd[pc[3]]) && !pc[1] && !pc[2] && !pc[4])
		{
			if (++pc[0] && ft_strchr("<>|", cmd[pc[3] + 1]))
				pc[3]++;
		}
		else if (cmd[pc[3]] == '&' && cmd[pc[3] + 1] == '&'
			&& !pc[1] && !pc[2] && !pc[4])
			pc[0] += 1 + 0 * (++pc[3]);
		if (pc[4] < 0)
			return (-2 + 0 * (ft_printf("\33[0;31mInvalid Syntax\33[0m\n")));
	}
	if (!pc[4])
		return (pc[0]);
	return (-2 + 0 * (ft_printf("\33[0;31mInvalid Syntax\33[0m\n")));
}

int	parse_modes(t_shell *shell, int **q)
{
	if ((shell->cmd[(*q)[3]] == '&'
		&& shell->cmd[(*q)[3] + 1] != '&') || (*q)[5])
		return (0);
	shell->mode = ft_charjoin(shell->mode, shell->cmd[(*q)[3]]);
	if (shell->cmd[(*q)[3]] == '>'
		&& shell->cmd[(*q)[3] + 1] == '>')
		shell->mode[ft_strlen(shell->mode) - 1] += 5 + (0 * (*q)[3]++);
	else if (shell->cmd[(*q)[3]] == '<'
		&& shell->cmd[(*q)[3] + 1] == '<')
		shell->mode[ft_strlen(shell->mode) - 1] += 5 + (0 * (*q)[3]++);
	else if (shell->cmd[(*q)[3]] == '|'
		&& shell->cmd[(*q)[3] + 1] == '|')
		shell->mode[ft_strlen(shell->mode) - 1] = '^' + (0 * (*q)[3]++);
	else if (shell->cmd[(*q)[3]] == '&'
		&& shell->cmd[(*q)[3] + 1] == '&')
		shell->mode[ft_strlen(shell->mode) - 1] = '&' + (0 * (*q)[3]++);
	return (1);
}

int	parse_parenthesis(t_shell *shell, int **q)
{
	if (shell->cmd[(*q)[3]] == '(')
	{
		if (!(*q)[5])
			shell->mode = ft_charjoin(shell->mode, shell->cmd[(*q)[3]]);
		(*q)[5]++;
		(*q)[3]++;
	}
	else if (shell->cmd[(*q)[3]] == ')')
	{
		(*q)[5]--;
		(*q)[3]++;
		if ((*q)[5] > 0)
			return (0);
		return (1);
	}
	return (0);
}

void	parse_commands_loop(t_shell *s, int **q)
{
	while (++(*q)[2] < (*q)[4])
	{
		(*q)[3]++;
		s->cmd_list[(*q)[2]] = ft_strdup("");
		while (s->cmd[(*q)[3]])
		{
			if (s->cmd[(*q)[3]] == '\'' && !(*q)[1])
				(*q)[0] = ((*q)[0] + 1) % 2;
			else if (s->cmd[(*q)[3]] == '"' && !(*q)[0])
				(*q)[1] = ((*q)[1] + 1) % 2;
			else if (!(*q)[0] && !(*q)[1] && ft_strchr("|<>&", s->cmd[(*q)[3]])
					&& parse_modes(s, q))
				break ;
			if (!(*q)[0] && !(*q)[1]
				&& (s->cmd[(*q)[3]] == '(' || s->cmd[(*q)[3]] == ')'))
			{
				if (parse_parenthesis(s, q))
					(*q)[3] += count_char(&s->cmd[(*q)[3]], ' ');
			}
			else
				s->cmd_list[(*q)[2]] = ft_charjoin(s->cmd_list[(*q)[2]],
						s->cmd[(*q)[3]++]);
		}
	}
	s->cmd_list[(*q)[2]] = NULL;
}

int	parse_commands(t_shell *shell)
{
	int	qsijc[7];
	int	cqdip[5];
	int	*p;

	shell->mode = ft_strdup("");
	qsijc[0] = 0;
	qsijc[1] = 0;
	qsijc[2] = -1;
	qsijc[3] = -1;
	cqdip[0] = 1;
	cqdip[1] = 0;
	cqdip[2] = 0;
	cqdip[3] = -1;
	cqdip[4] = 0;
	qsijc[4] = count_cmd(shell->cmd, &cqdip[0]);
	qsijc[5] = 0;
	shell->fix = 0;
	shell->cmd_list = NULL;
	shell->cmd_list = malloc(sizeof(char *) * (qsijc[4] + 1));
	if (!shell->cmd_list || !shell->mode || qsijc[4] == -2)
		return (1);
	p = &qsijc[0];
	parse_commands_loop(shell, &(p));
	return (debug_pipe(shell, 0));
}
