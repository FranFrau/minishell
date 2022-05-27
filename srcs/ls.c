#include "minishell.h"

void	read_dir(DIR *dir, char **list)
{
	struct dirent	*el;
	int				i;

	el = readdir(dir);
	while (el)
	{
		if (ft_strncmp(el->d_name, ".", 1))
		{
			i = -1;
			while (el->d_name[++i])
				*list = ft_charjoin(*list, el->d_name[i]);
			*list = ft_charjoin(*list, '\n');
		}
		el = readdir(dir);
	}
}

char	**list_dir(char *path)
{
	DIR				*dir;
	char			*tmp;
	char			**list;

	dir = opendir(path);
	if (!dir)
		return (NULL);
	tmp = malloc(sizeof(char) * 1);
	if (!tmp)
		return (NULL);
	tmp[0] = '\0';
	read_dir(dir, &tmp);
	list = ft_split(tmp, '\n');
	closedir(dir);
	free(tmp);
	return (list);
}

void	copy_list_dir(char **list, t_shell *shell)
{
	int	i;
	int	j;

	i = -1;
	while (list[++i])
	{
		j = -1;
		while (list[i][++j])
			shell->pipe = ft_charjoin(shell->pipe, list[i][j]);
		shell->pipe = ft_charjoin(shell->pipe, '\n');
	}
}

void	ls(t_shell *shell)
{
	char	**list;
	char	*path;

	if (shell->words[1])
		path = ft_strdup(shell->words[1]);
	else
		path = ft_strdup(".");
	list = list_dir(path);
	shell->pipe = ft_strdup("");
	if (!list)
	{
		ft_printf("ls: cannot access '%s': No such file or directory\n", path);
		shell->exit_code = ft_strdup("1");
		return ;
	}
	copy_list_dir(list, shell);
	free(shell->exit_code);
	shell->exit_code = ft_strdup("0");
	free_matrix(list);
	free(path);
}
