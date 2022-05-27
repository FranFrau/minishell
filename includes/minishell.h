/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:40:22 by tde-nico          #+#    #+#             */
/*   Updated: 2022/03/22 13:40:22 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "\033[0;35mminishell>\033[0m "

int	g_exit_code;

typedef struct s_pipe
{
	int				pipes[2];
	struct s_pipe	*next;
	struct s_pipe	*previous;
}	t_pipe;

typedef struct s_shell
{
	char	**env;
	char	*cmd;
	char	**cmd_list;
	char	**words;
	char	*pipe;
	char	*path;
	char	*exit_code;
	char	*mode;
	int		fix;
	int		i;
	int		j;
	int		nest;
	t_pipe	*pipes;
}	t_shell;

// utils
int		free_matrix(char **matrix);
void	free_shell(t_shell *shell, int mod);
char	*get_line(int fd);
void	get_pipe_exit(int fd, t_shell *shell);
char	*get_path(char **env);

// str_utils
char	*ft_strcdup(const char *src, char c);
char	*ft_charjoin(char *s1, char s2);
char	*ft_strndup(const char *src, size_t len);
char	**ft_arrdup(char **src);
void	ft_strappend(char **dst, char *to_append);

// signal
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	handle_child_sigint(int sig);
void	handle_child_sigquit(int sig);

// debug
void	debug_cmd(char *cmd, char **cmd_split);
int		debug_pipe(t_shell *shell, int verbose);
int		debug_pipe_final(t_shell *shell, int verbose);

// env_handler
void	init_env(char **envp, char ***env);
void	replace_env(char **cmd, t_shell *shell);

// cmd_parse
int		parse_commands(t_shell *shell);

// cmd_split
int		count_char(char *cmd, char c);
char	**split_cmd(char *cmd, int quotes, char *pipe_in);

// echo cd export unset env
void	echo(t_shell *shell);
int		change_dir(t_shell *shell);
void	cd(t_shell *shell);
void	print_sorted_env(t_shell *shell);
void	export(t_shell *shell);
void	unset(t_shell *shell);
void	env(t_shell *shell);

// ls
char	**list_dir(char *path);
void	ls(t_shell *shell);

// bin_process
void	pipe_process(t_shell *shell);
void	execute_pipe(t_shell *shell);

// cmd_process
int		count_quotes(char *cmd);
int		process_cmd(char **cmd, t_shell *shell);

// pipeline
void	execute_pipeline(t_shell *shell);

// redirections
int		process_in_mode(t_shell *shell, int *i);
void	process_out_mode(t_shell *shell, int *i);

// parse_wildcard
void	parse_wild(char **new, char **cmd);

// wildcards
void	replace_wild(char **cmd, t_shell *shell);

// command_process
int		fix_end_loop(t_shell *shell);
int		cmds_process_loop(t_shell *shell);

//	parenthesis
void	rec_process(t_shell *shell, int *i);

// main
int		cmds_process_loop(t_shell *shell);

#endif