#include "minishell.h"

extern	void	rl_replace_line(const char *text, int clear_undo);

void	handle_sigint(int sig)
{
	(void)sig;
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
}

void	handle_child_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_exit_code = 130;
}

void	handle_child_sigquit(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_exit_code = 131;
}
