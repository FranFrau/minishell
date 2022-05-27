#include "minishell.h"

void	ft_envappend(char **dst, char *to_append)
{
	int	i;
	int	appended;

	i = -1;
	appended = 0;
	while (to_append[++i])
	{
		*dst = ft_charjoin(*dst, to_append[i]);
		if (to_append[i] == '=' && !appended)
		{
			appended = 1;
			*dst = ft_charjoin(*dst, '\"');
		}
	}
	*dst = ft_charjoin(*dst, '\"');
}

char	**sort(char **to_sort)
{
	int		i;
	int		j;
	int		k;
	char	**sorted;

	i = 0;
	while (to_sort[i])
		++i;
	sorted = malloc(sizeof(char *) * (i + 1));
	sorted[i] = NULL;
	i = -1;
	while (to_sort[++i])
	{
		j = -1;
		k = 0;
		while (to_sort[++j])
			if (ft_strncmp(to_sort[i], to_sort[j], ft_strlen(to_sort[i])) > 0)
				k++;
		sorted[k] = to_sort[i];
	}
	return (sorted);
}

void	print_sorted_env(t_shell *shell)
{
	char	**sorted;
	int		i;

	sorted = sort(shell->env);
	i = -1;
	while (sorted[++i])
	{
		ft_strappend(&shell->pipe, "declare -x ");
		ft_envappend(&shell->pipe, sorted[i]);
		shell->pipe = ft_charjoin(shell->pipe, '\n');
	}
	free(sorted);
}
