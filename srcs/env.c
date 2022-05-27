#include "minishell.h"

void	env(t_shell *shell)
{
	int		i;
	int		j;

	i = -1;
	shell->pipe = malloc(sizeof(char) * 1);
	shell->pipe[0] = '\0';
	while (shell->env[++i])
	{
		j = -1;
		while (shell->env[i][++j])
			shell->pipe = ft_charjoin(shell->pipe, shell->env[i][j]);
		shell->pipe = ft_charjoin(shell->pipe, '\n');
	}
	free(shell->exit_code);
	shell->exit_code = ft_strdup("0");
}
