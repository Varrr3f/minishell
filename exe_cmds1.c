#include "minishell.h"

void	get_command_position(t_cmds *cmd, t_shell **shell, int cmd_pos, int in)
{
	if (cmd_pos == 0)
	{
        // printf("%d\n", (*shell)->pipes[0][1]);
        dup2((*shell)->pipes[0][1], STDOUT_FILENO); //первый дупим на вывод в трубу
	    handle_redirects(cmd, shell, in);
	    close((*shell)->pipes[0][0]);
    }
	else if (cmd_pos == (*shell)->cmd_index - 1)
	{
        // printf("%d\n", (*shell)->pipes[(*shell)->cmd_index - 2][0]);
        // printf("%d\n", (*shell)->pipes[(*shell)->cmd_index - 2][1]);
        handle_redirects(cmd, shell, in);
	    dup2((*shell)->pipes[(*shell)->cmd_index - 2][0], STDIN_FILENO); //последний дупим на ввод из трубы
	    close((*shell)->pipes[(*shell)->cmd_index - 2][1]);
    }
	else
	{
        // printf("%d\n", (*shell)->pipes[cmd_pos - 1][0]);
        // printf("%d\n", (*shell)->pipes[cmd_pos][1]);
        dup2((*shell)->pipes[cmd_pos - 1][0], STDIN_FILENO); //средние дупим на ввод и вывод
	    dup2((*shell)->pipes[cmd_pos][1], STDOUT_FILENO);
    }
}

int	get_args_quantity(t_list *args)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = args;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**get_command_arguments(t_list *args)
{
	t_list	*curr;
	char	**cmd_args;
	int		quan;
	int		i;

	i = 0;
	curr = args;
	quan = get_args_quantity(args);
	cmd_args = (char **)malloc(sizeof(char *) * (quan + 1));
	if (!cmd_args)
		error("Error\n");
	while (i < quan)
	{
		cmd_args[i] = ft_strdup(curr->content);
		if (!cmd_args[i])
			error("Error\n");
		curr = curr->next;
		i++;
	}
	cmd_args[i] = NULL;
	return (cmd_args);
}



char	**parse_paths(t_envlist *list)
{
	char	**my_paths;	
	char	*path_env;
	int		i;

	i = 0;
	path_env = find_env(list, "PATH");
	if (!path_env)
		return (NULL);
	my_paths = ft_split(path_env, ':');
	if (!my_paths)
		error("Malloc error\n");
	while (my_paths[i])
	{
		my_paths[i] = ft_strjoin(my_paths[i], "/");
		if (!my_paths[i])
			error("Malloc error\n");
		i++;
	}
	return (my_paths);
}

void	handle_no_path(char **path, char ***cmd_args)
{
	*path = ft_strjoin("/", (*cmd_args)[0]);
	if (!*path)
		error("Error\n");
	if (access(*path, F_OK))
		*path = NULL;
}

void	exec_system_bin(t_cmds *cmd, char **path, char ***cmd_args)
{
	char	**paths;
	int		i;

	i = 0;
	paths = parse_paths(cmd->envs);
    // printf("path: %s\n", paths[0]);
    // printf("path: %s\n", paths[1]);
    // printf("path: %s\n", paths[3]);
    // printf("path: %s\n", paths[4]);
    // printf("path: %s\n", paths[5]);
    // printf("path: %s\n", paths[6]);
	*cmd_args = get_command_arguments(cmd->args);
	if (!(*cmd_args))
		error("Error\n");
	while (paths && paths[i])
	{
		*path = ft_strjoin(paths[i], (*cmd_args)[0]); //чистить
		if (!*path)
			error("Error\n");
		if (access(*path, F_OK) == 0)
			break ;
		free(paths[i]);
		free(*path);
		*path = NULL;
		i++;
	}
	if (!*path)
		handle_no_path(path, cmd_args);
	free(paths);
}

void	handle_empty_path(char *path, t_cmds *cmd, char **cmd_args, t_shell **shell)
{
	if (path == NULL && !find_env(cmd->envs, "PATH"))
	{
		(*shell)->exit_status = 127;
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, cmd_args[0], ft_strlen(cmd_args[0]));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		exit((*shell)->exit_status);
	}
	else if (path == NULL)
	{
		(*shell)->exit_status = 127;
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, cmd_args[0], ft_strlen(cmd_args[0]));
		write(STDERR_FILENO, ": cmd not found\n", 20);
		exit((*shell)->exit_status);
	}
}

void	my_exec(t_shell **shell, char *path, char **cmd_args, char **envp)
{
	int	exec_res;

	(*shell)->exit_status = 0;
	exec_res = execve(path, cmd_args, envp);
	if (exec_res == -1)
	{
		(*shell)->exit_status = 127;
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, cmd_args[0], ft_strlen(cmd_args[0]));
		write(STDERR_FILENO, ": cmd not found\n", 20);
		exit((*shell)->exit_status);
	}
	if (exec_res == -1 && cmd_args && *cmd_args)
	{
		(*shell)->exit_status = 127;
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, cmd_args[0], ft_strlen(cmd_args[0] + 1));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		exit((*shell)->exit_status);
	}
}

void	launch_command(t_cmds *cmd, char **envp, t_shell **shell)
{
	char	*path;
	char	**cmd_args;

	path = NULL;
	cmd_args = get_command_arguments(cmd->args);
    // printf("%s\n", cmd_args[0]);
    // printf("%s\n", cmd_args[1]);
    // printf("%s\n", cmd_args[2]);
    // printf("%s\n", cmd_args[3]);
	if (!cmd_args)
		error("error");
	if (is_built_in(cmd->args->content))
	{
		built_ins(&(cmd->envs), cmd, shell, envp);
		exit(0);
	}
	else if (ft_strchr(cmd->args->content, '/') != NULL)
    {
        // printf("////obrab\n");
        // exec_non_system_bin(cmd, &path, &cmd_args);
        cmd_args = get_command_arguments(cmd->args);
	    if (!*cmd_args)
		    error("Error");
	    path = &(*cmd_args)[0];
    }
	else
		exec_system_bin(cmd, &path, &cmd_args);
	handle_empty_path(path, cmd, cmd_args, shell);
	my_exec(shell, path, cmd_args, envp);
	(*shell)->exit_status = 1;
	exit((*shell)->exit_status);
}

void	fork_error(t_shell **shell)
{
	(*shell)->exit_status = 128;
	write(STDERR_FILENO, "minishell: fork: Error", 24);
	exit((*shell)->exit_status);
}

pid_t	watch_child_process(t_shell **shell, t_cmds **cmds, int in, char **envp)
{
	int		counter;
	pid_t	pid;

	counter = 0;
	set_signals_two(cmds);
	while (cmds[counter])
	{
		pid = fork();
		if (pid == 0)
		{
            // printf("%d\n", (*shell)->cmd_index);
			if ((*shell)->cmd_index > 1) //можно убрать ?
			{
				get_command_position(cmds[counter], shell, counter, in);
				close_all_pipes((*shell)->pipes);
			}
			else
				handle_redirects(cmds[counter], shell, in); //можно убрать ?
			launch_command(cmds[counter], envp, shell);
		}
		else if (pid == -1)
			fork_error(shell);
		counter++;
	}
	return_signals_parent_process();
	return (pid);
}

void	get_child_exit_status(int *status)
{
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		*status = WTERMSIG(*status);
	else if (WIFSTOPPED(*status))
		*status = WSTOPSIG(*status);
}

void	wait_child_processes(t_shell **shell, pid_t id)
{
	pid_t	process;
	int		status;
	int		i;

	status = 0;
	i = 0;
	while (i < (*shell)->cmd_index)
	{
		process = waitpid(-1, &status, 0); //ожидает пока выполнится любой дочерний процесс
		if (id == process)
		{
			get_child_exit_status(&status);
			(*shell)->exit_status = status;
		}
		i++;
	}
}

void	execute_bin(t_cmds **cmds, t_shell **shell, char **envp, int in)
{
	pid_t	pid;

	(*shell)->exit_status = 0;
	pid = watch_child_process(shell, cmds, in, envp);
	close_all_pipes(((*shell)->pipes));
	wait_child_processes(shell, pid);
}