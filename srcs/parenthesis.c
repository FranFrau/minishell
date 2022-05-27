#include "minishell.h"

void	rec_process(t_shell *shell, int *i)
{
	t_shell	fake;

	fake.cmd = ft_strdup(shell->cmd_list[(*i)]);
	fake.exit_code = ft_strdup(shell->exit_code);
	fake.env = ft_arrdup(shell->env);
	fake.fix = 0;
	fake.nest = shell->nest + 1;
	fake.pipe = NULL;
	if (shell->pipe != NULL)
		fake.pipe = ft_strdup(shell->pipe);
	fake.path = ft_strdup(shell->path);
	cmds_process_loop(&fake);
	if (shell->pipe != NULL)
		free(shell->pipe);
	shell->pipe = ft_strdup(fake.pipe);
	free(shell->exit_code);
	shell->exit_code = ft_strdup(fake.exit_code);
	free_shell(&fake, 2);
	(shell->fix)++;
}
