#include "minishell.h"

void	debug_cmd(char *cmd, char **cmd_split)
{
	int	i;

	i = -1;
	ft_printf("\ncmd: |%s|\n", cmd);
	while (cmd_split[++i])
	{
		if (cmd_split[i][0] == 0)
			ft_printf("words: |\\0|\n");
		else
			ft_printf("words: |%s|\n", cmd_split[i]);
	}
}

int	debug_pipe_final(t_shell *shell, int verbose)
{
	int		i;
	int		j;
	t_pipe	*p;

	i = 0;
	while (shell->cmd_list[i])
		i++;
	j = -1;
	while (shell->mode[++j])
	{
		if (shell->mode[j] && ft_strchr("<>AC", shell->mode[j]))
			i--;
	}
	while (i--)
	{
		p = malloc(sizeof(t_pipe *));
		if (shell->pipes)
			shell->pipes->previous = p;
		p->next = shell->pipes;
		p->previous = NULL;
		shell->pipes = p;
	}
	(void)verbose;
	return (0);
}

int	debug_pipe(t_shell *shell, int verbose)
{
	if ((ft_strnstr(shell->mode, "|", ft_strlen(shell->mode))
			|| ft_strnstr(shell->mode, "<", ft_strlen(shell->mode)))
		&& !ft_strnstr(shell->mode, "A", ft_strlen(shell->mode)))
	{
		free(shell->exit_code);
		replace_env(&shell->cmd, shell);
		shell->exit_code = ft_itoa(system(shell->cmd));
		if (verbose)
		{
			debug_cmd(shell->cmd, shell->env);
			ft_printf("\nexit_code: |%s|\n", shell->exit_code);
			ft_printf("\ncmd: |%s|\n", shell->mode);
		}
		return (1);
	}
	return (0);
}
