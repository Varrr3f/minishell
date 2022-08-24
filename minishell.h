/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:28:58 by ocapers           #+#    #+#             */
/*   Updated: 2022/06/28 17:33:28 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <termios.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "libft/libft.h"
# include "readline/tilde.h"
# include "readline/rlconf.h"
# include "readline/rlstdc.h"
# include "readline/history.h"
# include "readline/keymaps.h"
# include "readline/readline.h"
# include "readline/chardefs.h"
# include "readline/rltypedefs.h"

int	g_exit_status;

typedef struct s_envlist
{
	char				*key;
	char				*value;
	struct s_envlist	*next;
}	t_envlist;

typedef struct s_redirs
{
	char	*name;
	int		type;
}	t_redirs;

typedef struct s_shell
{
	int				**pipes;
	int				shell_level;
	int				fd_in;
	int				fd_out;
	int				num_of_process;
}				t_shell;

typedef struct s_cmds
{
	t_envlist		*envlist;
	t_shell			*shell;
	t_redirs		**redirs;
	t_list			*args;
}	t_cmds;

void		envp_to_list_del(t_envlist **vars, char *key);
t_envlist	*envp_add_init(char *key, char *value);
void		envlist_clear(t_envlist **vars);
int			num_of_list_elems(t_list *args);
t_envlist	*envlist_key_value(char **envp);
void		reading_str(t_envlist **envlist, t_shell **shell, char **envp);
void		rl_replace_line(const char *text, int clear_undo);
void		set_shell_level(t_envlist *envlist, t_shell *shell);
void		error(char *msg);
void		tty_hide_input(void);
void		catch_signals(void);
void		*sigint_handler(int sig_num);
void		sig_heredoc(int sig);
void		quotes_check(char c, int *s_q, int *d_q);
t_cmds		**parser(char *str, t_envlist *envlist, t_shell *shell);
void		set_arguments(char *line, t_cmds *cmd);
void		set_redirs(char *line, t_cmds *cmd);
char		*quotes_del(char *str, t_cmds *cmd);
int			get_num_of_commands(t_cmds **cmds);
void		clearing(t_cmds ***cmds);
int			check_str1(char *str);
int			check_str2(char *str);
char		*redirs_del(char *str);
char		*spaces_del(char *str);
bool		tabs_or_spaces(char *str);
void		envp_to_list_back(t_envlist **vars, t_envlist *new_var);
char		*find_envp(t_envlist *list, const char *key);
void		c_fork(int signum);
void		sigquit_handler(int num);
void		*sig_fork(int num);
void		return_signals_parent_process(void);
void		set_signals(t_cmds **cmds);
int			num_of_elems(char *str, int i, char **value, t_cmds *cmd);
char		*change_path(char *str, int *index, t_cmds *cmd);
int			builtins_check(char *cmd);
void		builtins_do(t_envlist **list, t_cmds *cmds, char **envp);
void		cd_ms(t_envlist **list, t_list *args);
void		handle_non_existing_path(t_list *args);
void		handle_empty_input(t_envlist *list);
void		echo_ms(t_list *args);
void		env_ms(t_envlist *list);
void		export_ms(t_envlist **list, t_list *args);
void		check_if_key_exists(t_envlist **list, char *arg);
char		**get_sorted_keys(char **keys, int size_of_list);
int			is_valid_env_key(char *token);
int			is_equal_sign(char *token);
int			get_list_size(t_envlist *list);
void		unset_ms(t_envlist **list, t_list *args);
void		exit_ms(t_list *args);
void		pwd_ms(t_list *args, t_envlist *list);
int			redirs_do(t_cmds *cmd, int in);
void		cmd_do(t_cmds *cmd, char **envp);
void		wait_child_pid(t_shell **shell, pid_t id);
void		standart_bin(t_cmds *cmd, char **path, char ***cmd_args);
void		path_bin(t_cmds *cmd, char **path, char ***cmdargs);
void		get_cmd_pos(t_cmds *cmd, t_shell **shell, int cmd_pos, int in);
void		here_doc(char *del, int in);
void		open_pipes(int **pipes, int cmnds);
void		close_all_pipes(int **pipes);
int			**pipes_init(int cmnds);
void		execve_in_pipes(t_cmds **cmds, t_shell **shell,
				char **envp, int in);
char		**get_command_arguments(t_list *args);
int			quotes_del2(t_cmds *cmd, t_list *args_copy);
void		redirects_clear(t_cmds *cmd);
int			array_clear(char ***array);
char		*quot_skip(char *str, int *index, char quote, t_cmds *cmd);
int			set_cmd(char *str, t_cmds **cmds, t_envlist *envlist,
				t_shell *shell);
void		left_redir(t_redirs *elem);
void		right_redir(t_redirs *elem);
void		child_process_help(t_shell **shell, t_cmds **cmds, int in, int i);

#endif