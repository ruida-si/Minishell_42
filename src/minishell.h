/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:20:47 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/04 18:20:47 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define FREE_BASE		1
# define FREE_STRUCT	2
# define FREE_CMD		4
# define FREE_PIPES		8
# define FREE_FDS		16
# define FREE_PIDS		32
# define FREE_REDIR		64

// colors
# define BLUE	"\001\033[44m\002"
# define RED	"\001\033[41m\002"
# define GREEN	"\001\033[42m\002"
# define RESET	"\001\033[0m\002"

// Includes
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include "../libft/libft.h"

// Structs -----

// Envp list
typedef struct s_env
{
	char			*var;
	char			*content;
	char			*content_qts;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

// Split Structs
typedef struct s_split
{
	char	**av;
	char	*s;
	char	c;
	int		i;
	int		j;
}	t_split;

//	Used in expand.c
typedef struct s_exp
{
	char	*first;
	char	*last;
	char	*var;
	int		start;
	char	*content;
}	t_exp;

//	Command struct
typedef struct s_cmd
{
	int		index;
	char	**cmd;
	char	*path;
	int		input_fd;
	int		output_fd;
	int		sts;
	int		builtin;
	int		redirin;
	int		redirout;
}	t_cmd;

// Main Struct
typedef struct s_mini
{
	char	*input;
	char	*prompt;
	char	**ap;
	char	**av;
	char	**envp;
	int		ppid;
	int		input_rec;
	int		**fds;
	int		*pid;
	int		childrun;
	int		pipes;
	int		chain_stop;
	char	**redirap;
	t_env	*export;
	t_exp	expand;
	t_cmd	*cmd;
}	t_mini;

//	Global Variables
extern int	g_exit_status;

//	Funcs

// Redirections
char	**exec_redir(t_mini *mini, int n);
int		is_redir(char *s);
void	here_doc(t_mini *ms, char *file, int n);
int		check_eof(char *file, char *buff);

//	Printf_fd
int		ft_printf_fd(int fd, const char *format, ...);

//	Initialization
t_mini	init(char **envp);
int		ft_getpid(void);
char	*get_input(t_mini *ms);
int		check_cmd(char *cmd);

//	Signals
void	ms_signals(void);
void	sighandler(int sig);
void	sigint_child(int sig);
void	sigint_heredoc(int sig);

//	Expand
char	*expand(char *s, t_mini *ms, int option);
int		expand_ok(char c);
void	expand_others(char c, t_mini *ms, int *i);
char	*extract_slash(char *s);
void	expand_2(char **s, int *i, t_mini *ms);
void	expand_quotes(char **s, int *a, t_mini *ms);

//	Parsing
int		parsing(t_mini *mini);
char	get_last_char(t_mini *mini);

//	Execute CMD
void	execute_cmd(t_mini *ms);
void	fork_proc(t_mini *ms, int proc, int pipes);
int		**crt_pipes(t_mini *ms, int pipes);
int		*crt_pid_arr(t_mini *ms, int pid_n, int pipes);
void	child_proc(t_mini *ms, int n, int pipes);
void	check_access(t_mini *ms, int pipes, int n);

//  ------ Builtins ----------
int		print_echo(t_mini *ms, char **av, int n);

// Export Funcs
int		exec_export(t_mini *ms, char **av, int np);
void	order_envp(t_mini *mini);
char	*check_content(char *content);
int		syntax_export(char *var, char *content, char *s, int i);
void	create_export(char *var, char *content, t_mini *mini, char c);
void	fill_content_qts(t_env *exprt, t_env *node, char *content, int opt);

// Other bultins
int		exec_unset(t_mini *ms, int n);
int		exec_pwd(t_mini *ms, int n);
int		exec_env(t_mini *ms, int n);
int		exec_exit(t_mini *ms, int n);

// CD
int		exec_cd(t_mini *ms, int n);
void	update_var(char *oldpwd, char *pwd, t_mini *mini);
char	*get_new_cwd(char *buffer);
int		cd_5(t_mini *ms, char **av);
char	*get_home(t_mini *ms, char *home);

//	Helper functions

// -- Split --
char	**ft_split_quotes(char *s, char c);
char	**ft_split_redir(char *s, char c);

// -- Others --
char	*get_str(char *s, int start, int end);
void	update_i(char *s, int *i, char c);
int		check_closed_quotes(char *input, int option);
int		char_quotes(char c);
char	*ft_getenv(char *var, t_mini *ms);
char	*ft_strjoin_3(char *path, char *cmd, char c);
char	*get_new_str(char *s);
int		cnt_strings(char **av);
int		pidnbr_cnt(t_mini *ms, int proc);
int		list_size(t_mini *ms);
int		char_redir(char c);
int		white_spaces(char c);
char	*check_quotes(char *file, int *quotes);

//	Memory Clean
void	clean_list(t_mini *ms);
void	free_mem(char **av);
void	split_memfree(t_mini *ms);
void	free_2strings(char *s1, char *s2);
void	close_pipes(t_mini *ms, int pipes);
int		exec_free(t_mini *ms, int pipes, int opt, int ret);
void	free_intarray(t_mini *ms, int pipes);
void	close_redir(t_mini *ms, int proc);
void	free_base(t_mini *ms);
void	free_cmd(t_mini *ms, int pipes);

#endif
