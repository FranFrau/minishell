#include "minishell.h"

int	pop(t_shell *shell, int index)
{
	char	**new;
	int		i;
	int		j;
	int		len;

	i = -1;
	j = 0;
	len = 0;
	while (shell->env[len])
		len++;
	new = malloc(sizeof(char *) * (len));
	if (!new)
		return (0 * ft_printf("Error unset var\n"));
	while (shell->env[++i] && i < len)
		if (i != index)
			new[j++] = ft_strdup(shell->env[i]);
	free_matrix(shell->env);
	new[j] = NULL;
	shell->env = new;
	return (1);
}

void	unset(t_shell *shell)
{
	int		len;
	int		i;
	int		j;

	i = -1;
	shell->pipe = ft_strdup("");
	while (shell->words[++i])
	{
		j = -1;
		len = ft_strlen(shell->words[i]);
		while (shell->env[++j])
		{
			if (!ft_strncmp(shell->env[j], shell->words[i], len)
				&& shell->env[j][len] == '=')
			{
				pop(shell, j);
				break ;
			}
		}
	}
	free(shell->exit_code);
	shell->exit_code = ft_strdup("0");
}
