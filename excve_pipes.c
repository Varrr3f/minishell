#include "minishell.h"

int exit_status;

void	handle_empty_path(char *path, t_cmds *cmd, char **cmdargs,
		t_shell **shell)
{
	if (path == NULL && !find_envp(cmd->envlist, "PATH"))
	{
		exit_status = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmdargs[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(exit_status);
	}
	else if (path == NULL)
	{
		exit_status = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmdargs[0], 2);
		ft_putstr_fd(": cmd not found\n", 2);
		exit(exit_status);
	}
}

void	my_exec(t_shell **shell, char *path, char **cmdargs, char **envp)
{
	int	exec_res;

	exit_status = 0;
	exec_res = execve(path, cmdargs, envp);
	if (exec_res == -1)
	{
		exit_status = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmdargs[0], 2);
		ft_putstr_fd(": cmd not found\n", 2);
		exit(exit_status);
	}
	if (exec_res == -1 && cmdargs && *cmdargs)
	{
		exit_status = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmdargs[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(exit_status);
	}
}

void	cmd_do(t_cmds *cmd, char **envp, t_shell **shell)
{
	char	*path;
	char	**cmdargs;

	path = NULL;
	cmdargs = get_command_arguments(cmd->args);
	if (!cmdargs)
		error("minishell: error of malloc\n");
	if (builtins_check(cmd->args->content))
	{
		builtins_do(&(cmd->envlist), cmd, shell, envp);
		exit(0);
	}
	else if (ft_strchr(cmd->args->content, '/') != NULL)
		path_bin(cmd, &path, &cmdargs);
	else
		standart_bin(cmd, &path, &cmdargs);
	handle_empty_path(path, cmd, cmdargs, shell);
	my_exec(shell, path, cmdargs, envp);
	exit_status = 1;
	exit(exit_status);
}

pid_t	watch_child_process(t_shell **shell, t_cmds **cmds, int in,
		char **envp)
{
	int		i;
	pid_t	pid;

	i = 0;
	set_signals(cmds);
	while (cmds[i])
	{
		pid = fork();
		if (pid == 0)
		{
			if ((*shell)->num_of_process > 1)
			{
				get_cmd_pos(cmds[i], shell, i, in);
				close_all_pipes((*shell)->pipes);
			}
			else
				redirs_do(cmds[i], shell, in);
			cmd_do(cmds[i], envp, shell);
		}
		else if (pid == -1)
		{
			exit_status = 128;
			ft_putstr_fd("minishell: error of fork\n", 2);
			exit(exit_status);
		}
		i++;
	}
	return_signals_parent_process();
	return (pid);
}

void	execve_in_pipes(t_cmds **cmds, t_shell **shell, char **envp, int in)
{
	pid_t	pid;
	int		i;

	i = 0;
	exit_status = 0;
	pid = watch_child_process(shell, cmds, in, envp);
	close_all_pipes(((*shell)->pipes));
	wait_child_pid(shell, pid);
}
