/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excve_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:58:09 by ocapers           #+#    #+#             */
/*   Updated: 2022/06/28 17:47:13 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_empty_path(char *path, t_cmds *cmd, char **cmdargs)
{
	if (path == NULL && !find_envp(cmd->envlist, "PATH"))
	{
		g_exit_status = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmdargs[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(g_exit_status);
	}
	else if (path == NULL)
	{
		g_exit_status = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(cmdargs[0], 2);
		write(2, "\n", 1);
		exit(g_exit_status);
	}
}

void	my_exec(char *path, char **cmdargs, char **envp)
{
	int	exec_res;

	g_exit_status = 0;
	exec_res = execve(path, cmdargs, envp);
	if (exec_res == -1)
	{
		g_exit_status = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(cmdargs[0], 2);
		write(2, "\n", 1);
		exit(g_exit_status);
	}
	if (exec_res == -1 && cmdargs && *cmdargs)
	{
		g_exit_status = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmdargs[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(g_exit_status);
	}
}

void	cmd_do(t_cmds *cmd, char **envp)
{
	char	*path;
	char	**cmdargs;

	path = NULL;
	cmdargs = get_command_arguments(cmd->args);
	if (!cmdargs)
		error("minishell: error of malloc\n");
	if (builtins_check(cmd->args->content))
	{
		builtins_do(&(cmd->envlist), cmd, envp);
		exit(0);
	}
	else if (ft_strchr(cmd->args->content, '/') != NULL)
		path_bin(cmd, &path, &cmdargs);
	else
		standart_bin(cmd, &path, &cmdargs);
	handle_empty_path(path, cmd, cmdargs);
	my_exec(path, cmdargs, envp);
	g_exit_status = 1;
	exit(g_exit_status);
}

pid_t	watch_child_process(t_shell **shell, t_cmds **cmds, int in, char **envp)
{
	int		i;
	pid_t	pid;

	i = -1;
	while (cmds[++i])
	{
		pid = fork();
		if (pid == 0)
		{
			child_process_help(shell, cmds, in, i);
			cmd_do(cmds[i], envp);
		}
		else if (pid == -1)
		{
			g_exit_status = 128;
			ft_putstr_fd("minishell: error of fork\n", 2);
			exit(g_exit_status);
		}
	}
	return_signals_parent_process();
	return (pid);
}

void	execve_in_pipes(t_cmds **cmds, t_shell **shell, char **envp, int in)
{
	pid_t	pid;
	int		i;

	i = 0;
	g_exit_status = 0;
	pid = watch_child_process(shell, cmds, in, envp);
	close_all_pipes(((*shell)->pipes));
	wait_child_pid(shell, pid);
}
