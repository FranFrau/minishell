#include "minishell.h"

int	end_loop(t_shell *shell, int mod)
{
	int	i;

	if (mod == 2)
		shell->pipe = ft_strdup("");
	free(shell->cmd);
	free_matrix(shell->cmd_list);
	if (!shell->pipe)
	{
		free(shell->mode);
		return (1);
	}
	i = 0;
	while (shell->mode[i] == '&')
		i++;
	if (i > 0 && shell->mode[i] == 0)
		ft_putstr_fd(shell->pipe, 1);
	if (mod == 1 && !(shell->mode[shell->fix - 1] == '&'
			&& !((shell->fix - 1) > 0
				&& ft_strchr("(<>AC", shell->mode[shell->fix - 2]))))
		ft_putstr_fd(shell->pipe, 1);
	if (!shell->nest)
		free(shell->pipe);
	free(shell->mode);
	return (0);
}

void	cmds_process_exetend(t_shell *shell, int *i)
{
	if (!process_in_mode(shell, i))
	{
		if (shell->mode[shell->fix - 1] == '&'
			|| shell->mode[shell->fix - 1] == '^')
		{
			free(shell->pipe);
			shell->pipe = NULL;
		}
		process_cmd(&shell->cmd_list[*i], shell);
	}
	process_out_mode(shell, i);
	if (shell->mode[shell->fix] == '^'
		&& ft_strncmp(shell->exit_code, "0", 2))
		ft_putstr_fd(shell->pipe, 1);
}

int	parsed_cmd_loop(t_shell *s, int *i)
{
	if (s->mode[s->fix] == '&')
	{
		if (!(s->fix > 0 && ft_strchr("(<>AC", s->mode[s->fix - 1])))
			ft_putstr_fd(s->pipe, 1);
		if (ft_strncmp(s->exit_code, "0", 2))
			return (1);
	}
	if (!s->pipe || (!ft_strncmp(s->exit_code, "127", 4)
			&& s->mode[s->fix] != '^'))
		return (1);
	if (s->mode[s->fix] == '^' && !ft_strncmp(s->exit_code, "0", 2))
	{
		if (!(s->mode[s->fix - 1] && s->mode[s->fix - 1] == '('))
			ft_putstr_fd(s->pipe, 1);
		while (ft_strchr("^(<>AC", s->mode[s->fix]) && s->mode[(s->fix)++])
			(*i) += (s->mode[s->fix - 1] != '(');
		if (s->mode[--(s->fix) + 1] == '(')
			(s->fix)++;
	}
	else if (s->fix > 0 && s->mode[s->fix - 1] == '^'
		&& ft_strchr("^", s->mode[s->fix]))
		ft_putstr_fd(s->pipe, 1);
	return (0);
}

int	fix_end_loop(t_shell *shell)
{
	int	i;

	i = 1;
	while (shell->mode[shell->fix - i] == '^')
		i++;
	if (i > 1 || (shell->mode[shell->fix - i]
			&& ft_strchr("(<>AC^", shell->mode[shell->fix - i])))
		return (end_loop(shell, 0));
	return (end_loop(shell, 1));
}

int	cmds_process_loop(t_shell *shell)
{
	int	i;

	i = -1;
	if (parse_commands(shell))
		return (end_loop(shell, 2));
	while (shell->cmd_list[++i])
	{
		if (shell->mode[shell->fix] == '(')
			rec_process(shell, &i);
		else
			cmds_process_exetend(shell, &i);
		if (parsed_cmd_loop(shell, &i))
			break ;
		(shell->fix)++;
	}
	if (shell->fix && !shell->mode[shell->fix - 1])
		(shell->fix)--;
	return (fix_end_loop(shell));
}
