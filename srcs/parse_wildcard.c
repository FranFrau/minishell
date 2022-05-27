#include "minishell.h"

int	only_wild(char **cmd, char ***list, char **new)
{
	int	j;
	int	i;

	j = -1;
	while ((*cmd)[++j])
	{
		if ((*cmd)[j] != '*')
			return (0);
	}
	j = -1;
	while ((*list)[++j])
	{
		i = -1;
		*new = ft_charjoin(*new, '\'');
		while ((*list)[j][++i])
			*new = ft_charjoin(*new, (*list)[j][i]);
		*new = ft_charjoin(*new, '\'');
		if ((*list)[j + 1])
			*new = ft_charjoin(*new, ' ');
	}
	free_matrix(*list);
	return (1);
}

void	start_end_wild(int (*jklsei)[6], char **cmd)
{
	(*jklsei)[3] = 1;
	if ((*cmd)[0] == '*')
		(*jklsei)[3] = 0;
	(*jklsei)[4] = 1;
	if ((*cmd)[ft_strlen((*cmd)) - 1] == '*')
		(*jklsei)[4] = 0;
	(*jklsei)[0] = -1;
}

int	tmp_check(char **new, char **ts, char **l, int (*jklsei)[6])
{
	if ((!ts[(*jklsei)[5] + 1] && (*jklsei)[5]))
		((*jklsei)[2])++;
	if ((*jklsei)[2] == (int)(ft_strlen(l[(*jklsei)[0]]) + 1)
		&& ((!ft_strncmp(l[(*jklsei)[0]], ts[0],
		ft_strlen(ts[0])) && (*jklsei)[3]) || !(*jklsei)[3])
		&& ((!l[(*jklsei)[0]][(*jklsei)[1]] && (*jklsei)[4]) || !(*jklsei)[4]))
	{
		(*jklsei)[5] = -1;
		*new = ft_charjoin(*new, '\'');
		while (l[(*jklsei)[0]][++(*jklsei)[5]])
			*new = ft_charjoin(*new, l[(*jklsei)[0]][(*jklsei)[5]]);
		*new = ft_charjoin(*new, '\'');
		*new = ft_charjoin(*new, ' ');
		return (1);
	}
	return (0);
}

void	wild_inner(char **new, char **ts, char **l, int (*jklsei)[6])
{
	char	*tmp;
	int		run;

	while (ts[++(*jklsei)[5]])
	{
		tmp = &(l[(*jklsei)[0]][(*jklsei)[1]]);
		run = 1;
		if (!ts[(*jklsei)[5] + 1])
			((*jklsei)[2])++;
		while (run)
		{
			tmp = ft_strnstr(tmp, &ts[(*jklsei)[5]][0], (*jklsei)[2]);
			if (!tmp)
				break ;
			(*jklsei)[1] += ft_strlen(ts[(*jklsei)[5]]) + tmp
				- &(l[(*jklsei)[0]][(*jklsei)[1]]);
			tmp += ft_strlen(&ts[(*jklsei)[5]][0]);
			if (tmp_check(new, ts, l, jklsei))
				run = 0;
			if (ts[(*jklsei)[5] + 1])
				(*jklsei)[5]++;
		}
		if (!run)
			break ;
	}
}

void	parse_wild(char **new, char **cmd)
{
	char	**ts;
	char	**l;
	int		jklsei[6];

	l = list_dir(".");
	if (only_wild(cmd, &l, new))
		return ;
	start_end_wild(&jklsei, cmd);
	ts = ft_split((*cmd), '*');
	while (l[++jklsei[0]])
	{
		jklsei[1] = 0;
		jklsei[5] = -1;
		jklsei[2] = ft_strlen(l[jklsei[0]]);
		wild_inner(new, ts, l, &jklsei);
	}
	free_matrix(l);
	free_matrix(ts);
}
