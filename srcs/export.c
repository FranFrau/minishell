#include "minishell.h"

int	alredy_exists(char **env, char *name)
{
	int		len;
	int		i;

	len = ft_strlen(name);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], name, len))
			if (env[i][len] == '=')
				return (1);
	}
	return (0);
}

int	append_name(t_shell *shell, char *name)
{
	char	**new;
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (shell->env[len])
		len++;
	new = malloc(sizeof(char *) * (len + 2));
	if (!new)
		return (0 * ft_printf("Error exportin variable\n"));
	while (shell->env[++i] && i < len)
		new[i] = ft_strdup(shell->env[i]);
	free_matrix(shell->env);
	new[i] = ft_strjoin(name, "=");
	new[++i] = NULL;
	shell->env = new;
	return (1);
}

void	append_value(t_shell *shell, char *name, char *value, int plus)
{
	char	*tmp;
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(name);
	while (shell->env[++i])
	{
		if (!ft_strncmp(shell->env[i], name, len) && shell->env[i][len] == '=')
		{
			if (plus)
				return (ft_strappend(&shell->env[i], value));
			tmp = shell->env[i];
			shell->env[i] = ft_strjoin(name, "=");
			free(tmp);
			tmp = shell->env[i];
			if (value)
			{
				shell->env[i] = ft_strjoin(shell->env[i], value);
				free(tmp);
			}
			return ;
		}
	}
}

void	export_var(t_shell *shell, char *word)
{
	char	**env_var;
	int		plus;

	env_var = ft_split(word, '=');
	plus = 0;
	if (env_var[0][ft_strlen(env_var[0]) - 1] == '+')
	{
		plus = 1;
		env_var[0][ft_strlen(env_var[0]) - 1] = '\0';
	}
	if (!alredy_exists(shell->env, env_var[0]))
	{
		if (!(append_name(shell, env_var[0])))
			return ;
	}
	append_value(shell, env_var[0], env_var[1], plus);
	free(env_var[0]);
	free(env_var[1]);
	free(env_var);
}

void	export(t_shell *shell)
{
	int	i;

	i = 0;
	shell->pipe = ft_strdup("");
	while (shell->words[++i])
	{
		export_var(shell, shell->words[i]);
	}
	if (i == 1)
		print_sorted_env(shell);
	free(shell->exit_code);
	shell->exit_code = ft_strdup("0");
}
