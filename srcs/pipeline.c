#include "minishell.h"

void	forked_pipe(t_shell *shell)
{
	int	status;

	if ((shell->mode[shell->fix] == '|' || shell->mode[shell->fix] == '>'
			|| shell->mode[shell->fix] == 'C')
		&& dup2(shell->pipes->pipes[1], 1) < 0)
		exit(1);
	if (shell->fix > 0 && shell->mode[shell->fix - 1] == '|'
		&& dup2(shell->pipes->previous->pipes[0], 0) < 0)
		exit(1);
	status = execve(shell->words[0], shell->words, shell->env);
	if (status < 0)
		status = 127;
	free_shell(shell, 1);
	exit(status);
}

void	wait_pipe(t_shell *shell, int pipe_open, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (pipe_open)
	{
		close(shell->pipes->pipes[0]);
		if (ft_strchr("^&(<A", shell->mode[shell->fix]))
			close(shell->pipes->pipes[1]);
	}
	if (shell->fix > 0 && ft_strchr("|", shell->mode[shell->fix - 1]))
		close(shell->pipes->previous->pipes[1]);
	free(shell->exit_code);
	shell->exit_code = ft_itoa(WEXITSTATUS(status));
	shell->pipe = ft_strdup("");
	shell->pipes = shell->pipes->next;
}

void	execute_pipeline(t_shell *shell)
{
	pid_t	pid;
	int		pipe_open;

	pipe_open = 0;
	if (shell->mode[shell->fix] == '|' || shell->mode[shell->fix] == '>'
		|| shell->mode[shell->fix] == 'C')
	{
		pipe_open = 1;
		pipe(shell->pipes->pipes);
	}
	signal(SIGINT, handle_child_sigint);
	pid = fork();
	if (pid < 0)
		exit(1 + 0 * ft_printf("Fork Error\n"));
	if (!pid)
		forked_pipe(shell);
	wait_pipe(shell, pipe_open, pid);
}
