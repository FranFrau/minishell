#include "minishell.h"

int	execute(t_shell *shell)
{
	int		status;

	status = 0;
	if (execve(shell->words[0], shell->words, shell->env))
		status = 127;
	free_shell(shell, 1);
	return (status);
}

int	execute_p(int fd, t_shell *shell)
{
	int		status;

	status = 0;
	if (shell->mode[shell->fix] && ft_strchr("|>C", shell->mode[shell->fix]))
		dup2(fd, 1);
	if (execve(shell->words[0], shell->words, shell->env))
		status = 127;
	write(fd, "\0", 1);
	free_shell(shell, 1);
	return (status);
}

void	pipe_process(t_shell *shell)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid == -1)
		exit(1 + 0 * ft_printf("Fork Error\n"));
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		exit(execute(shell));
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		waitpid(pid, NULL, 0);
	}
}

void	execute_pipe(t_shell *shell)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	g_exit_code = 0;
	pipe(fd);
	signal(SIGQUIT, handle_child_sigquit);
	signal(SIGINT, handle_child_sigint);
	pid = fork();
	if (pid == -1)
		exit(1 + 0 * ft_printf("Fork Error\n"));
	if (!pid)
	{
		close(fd[0]);
		exit(execute_p(fd[1], shell));
	}
	waitpid(pid, &status, 0);
	close(fd[1]);
	free(shell->exit_code);
	if (!g_exit_code)
		shell->exit_code = ft_itoa(WEXITSTATUS(status));
	else
		shell->exit_code = ft_itoa(g_exit_code);
	get_pipe_exit(fd[0], shell);
}
