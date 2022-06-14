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
# include "readline/tilde.h"
# include "readline/rlconf.h"
# include "readline/rlstdc.h"
# include "readline/history.h"
# include "readline/keymaps.h"
# include "readline/readline.h"
# include "readline/chardefs.h"
# include "readline/rltypedefs.h"
# include "libft/libft.h"

typedef struct s_envlist
{
	char				*key;
	char				*value;
	struct s_envlist	*next;
}	t_envlist;

typedef struct s_shell
{
	int exit_status;
	int	level;
	int	fd_in;
	int	fd_out;
	int	cmd_index;
	int	**pipes;
}	t_shell;

typedef struct s_redirs
{
	char	*word;
	int		type;
}	t_redirs;

typedef struct s_cmds
{
	t_redirs		**redirs;
	t_list			*args;
	t_envlist		*envs;
	t_shell			*shell;
}	t_cmds;

t_envlist	*envp_to_envlist(char **envp);
void	set_key_value_list(t_envlist *first_two_elems, t_envlist **envlist);
t_envlist	*set_first_key_value(char *key, char *value);
void	error(char *error);
int set_level(t_envlist *envlist);
void	init_shell(t_shell *shell, t_envlist *envlist);

void	tty_input(void);
void	*sigint_handler(int sig_num);
void	set_signals(void);
void	set_signals_two(t_cmds **commands);
void	*sig_fork(int num);
void	sigquit_handler(int num);
void	return_signals_parent_process(void);

t_cmds  **parser(char *str, t_envlist *envlist, t_shell *shell);
int get_count_cmds(char *str);
void	quotes_check(int *s_quote, int *d_quote, char ch);
t_cmds	*set_cmd(char *str,  t_envlist *envlist, t_shell *shell);
void	set_redirs_to_cmd(t_cmds *cmd, char *str);
int	get_type_of_redir(char *str, int *i);
char *get_word_of_redir(char *str, int i[5]);

char	*del_redirects(char *str);
// void	go_through_redirects(char *str, int i[5]);
char	*del_spaces(char *str);
void	get_cmd_arguments(char *str, t_cmds *cmd);
t_cmds	*get_cmd_two(t_cmds **cmd);
char	*del_quotes(char *str, t_cmds *cmd);
char	*strip_quotes(char *str, int *index, char quote, t_cmds *cmd);
char	*replace_path(char *str, int *index, t_cmds *cmd);
int	get_delta_of_indexes(char *str, int i, char **value, t_cmds *cmd);

void	execute_cmds(t_cmds **cmds, t_shell **shell, char **envp, char *line);
int	get_num_of_commands(t_cmds **commands);
int	**pipes_loop(int cmnds);
void	open_pipes(int **pipes, int cmnds);
void	close_all_pipes(int **pipes);
int	is_built_in(char *command);
void	built_ins(t_envlist **list, t_cmds *commands, t_shell **shell, char **envp);

void	here_doc(char *del, t_shell **shell, int in);

void	sig_heredoc(int sig);

void	handle_left_redir(t_redirs *elem, t_shell **shell);
void	handle_right_redir(t_redirs *elem, t_shell **shell);

void	pwd_ms(t_shell **shell, t_list *args, t_envlist *list);
char	*find_env(t_envlist *list, const char *key);
void	echo_ms(t_list *args, t_shell **shell);
int	echo_help(t_list *curr);
void	env_ms(t_envlist *list, t_shell **shell);

int	handle_redirects(t_cmds *command, t_shell **shell, int in);

void	execute_bin(t_cmds **commands, t_shell **shell, char **envp, int in);
pid_t	watch_child_process(t_shell **shell, t_cmds **commands, int in, char **envp);
void	launch_command(t_cmds *command, char **envp, t_shell **shell);
char	**get_command_arguments(t_list *args);
int	get_args_quantity(t_list *args);
void	wait_child_processes(t_shell **shell, pid_t id);
void	get_child_exit_status(int *status);
void	fork_error(t_shell **shell);
void	my_exec(t_shell **shell, char *path, char **cmdargs, char **envp);
void	handle_empty_path(char *path, t_cmds *command, char **cmdargs, t_shell **shell);
void	exec_system_bin(t_cmds *command, char **path, char ***cmd_args);
void	handle_no_path(char **path, char ***cmd_args);
char	**parse_paths(t_envlist *list);
void	get_command_position(t_cmds *command, t_shell **shell, int cmd_pos, int in);

void	ft_free_command_redirects(t_cmds *command);
int	ft_array_clear(char ***array);
void	commands_clear(t_cmds ***commands);

void	execute_cd(t_envlist **list, t_list *args, t_shell **shell);
void	handle_cd_arguments(t_list *args, t_shell **shell, t_envlist *list);
void	change_new_pwd_environ(t_envlist **list, char *new_path);
void	change_old_pwd_environ(t_envlist **list, char *old_path);
void	handle_non_existing_path(t_list *args, t_shell **shell);
void	handle_empty_input(t_envlist *list, t_shell **shell);
void	handle_unset_home(t_shell **shell);

#endif