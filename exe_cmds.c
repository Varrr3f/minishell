#include "minishell.h"

int	get_num_of_commands(t_cmds **commands)
{
	int	i;

	i = 0;
	while (commands && commands[i])
		i++;
	return (i);
}

int	is_built_in(char *command)
{
	if (ft_strncmp(command, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(command, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(command, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(command, "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(command, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(command, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(command, "export", 7) == 0)
		return (1);
	return (0);
}

void	built_ins(t_envlist **list, t_cmds *commands, t_shell **shell, char **envp)
{
	(void)envp;
	if (!commands->args)
		return ;
	if (ft_strncmp(commands->args->content, "pwd", 4) == 0)
		pwd_ms(shell, commands->args, *list);
    else if (ft_strncmp(commands->args->content, "echo", 5) == 0)
		echo_ms(commands->args, shell);
	// else if (ft_strncmp(commands->args->content, "env", 4) == 0)
	// 	env_ms(*list, shell);
    // else if (ft_strncmp(commands->args->content, "exit", 5) == 0)
	// 	exit_ms(shell, commands->args);
	// else if (ft_strncmp(commands->args->content, "unset", 6) == 0)
	// 	unset_ms(list, commands->args, shell);
	// else if (ft_strncmp(commands->args->content, "cd", 3) == 0)
	// 	cd_ms(list, commands->args, shell);
	// else if (ft_strncmp(commands->args->content, "export", 7) == 0)
	// 	export_ms(list, commands->args, shell);
}

void	here_doc(char *del, t_shell **shell, int in)
{
	char	*line;
	int		fd;

	(*shell)->exit_status = 0;
	fd = open("/tmp/file", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		error("open\n");
	while (true)
	{
		line = get_next_line(in);
		if (!line)
			break ;
		if (ft_strncmp(del, line, ft_strlen(del)) == 0
			&& ft_strlen(del) == ft_strlen(line) - 1)
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	fd = open("/tmp/file", O_RDONLY, 0777);
	if (fd == -1)
		error("open\n");
	dup2(fd, STDIN_FILENO);
}

void	handle_left_redir(t_redirs *elem, t_shell **shell)
{
	int	fd;

	fd = open(elem->word, O_RDONLY, 0777);
	if (fd == -1)
	{
		(*shell)->exit_status = 1;
		write(2, "minishell: ", 11);
		write(2, elem->word, ft_strlen(elem->word) + 1);
		write(2, ": No such file or directory\n", 28);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
}

void	handle_right_redir(t_redirs *elem, t_shell **shell)
{
	int	fd;

	fd = open(elem->word, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
	{
		(*shell)->exit_status = 2;
		error("open\n");
	}
	dup2(fd, STDOUT_FILENO);
}

void	open_files(t_redirs *elem, t_shell **shell, int in)
{	
	int	fd;

	if (elem->type == 0)
		handle_right_redir(elem, shell);
	if (elem->type == 1)
		handle_left_redir(elem, shell);
	if (elem->type == 2)
	{
		fd = open(elem->word, O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (fd == -1)
		    error("open\n");
		dup2(fd, STDOUT_FILENO);
	}
	if (elem->type == 3)
	{
		signal(SIGINT, (void *)sig_heredoc);
		here_doc(elem->word, shell, in);
	}
}

int	handle_redirects(t_cmds *command, t_shell **shell, int in)
{
	int	i;

	i = 0;
	while (command->redirs && command->redirs[i])
	{
		open_files(command->redirs[i], shell, in);
		i++;
	}
	return (0);
}

void	execute_cmds(t_cmds **cmds, t_shell **shell, char **envp, char *line)
{
	int	in;
	int	out;

	(*shell)->cmd_index = get_num_of_commands(cmds);
	if ((*shell)->cmd_index > 1)
		(*shell)->pipes = pipes_loop((*shell)->cmd_index);
	if (*line != '\0')
	{
		in = dup(STDIN_FILENO);
		out = dup(STDOUT_FILENO);
		if (is_built_in(cmds[0]->args->content) && !cmds[1])
		{
            printf("aaaa\n");
			handle_redirects(cmds[0], shell, in);
			built_ins(&(cmds[0]->envs), cmds[0], shell, envp);
		}
		// else
		// 	execute_bin(cmds, shell, envp, in);
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
	}
}