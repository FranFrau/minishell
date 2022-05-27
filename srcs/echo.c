#include "minishell.h"

void	echo(t_shell *shell)
{
	int		i;
	int		j;

	i = 0;
	shell->pipe = malloc(sizeof(char) * 1);
	shell->pipe[0] = '\0';
	while (shell->words[i + 1] && !ft_strncmp(shell->words[i + 1], "-n", 3))
		i++;
	while (shell->words[++i])
	{
		j = -1;
		while (shell->words[i][++j])
			shell->pipe = ft_charjoin(shell->pipe, shell->words[i][j]);
		if (shell->words[i + 1])
			shell->pipe = ft_charjoin(shell->pipe, ' ');
	}
	if (!shell->words[1] || ft_strncmp(shell->words[1], "-n", 2))
		shell->pipe = ft_charjoin(shell->pipe, '\n');
	free(shell->exit_code);
	shell->exit_code = ft_strdup("0");
}

/*
void	echo(t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->words[i + 1] && !ft_strncmp(shell->words[i + 1], "-n", 3))
		i++;
	while (shell->words[++i])
	{
		ft_printf("%s", shell->words[i]);
		if (shell->words[i + 1])
			write(1, " ", 1);
	}
	if (!shell->words[1] || ft_strncmp(shell->words[1], "-n", 2))
		write(1, "\n", 1);
	shell->pipe = ft_strdup("");
	free(shell->exit_code);
	shell->exit_code = ft_strdup("0");
}
*/
