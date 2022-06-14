#include "minishell.h"

int	get_num_of_commands(t_cmds **cmds)
{
	int	i;

	i = 0;
	while (cmds && cmds[i])
		i++;
	return (i);
}

int	is_built_in(char *cmd)
{
	// printf("%s\n", cmd);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	return (0);
}

void	built_ins(t_envlist **list, t_cmds *cmds, t_shell **shell, char **envp)
{
	(void)envp;
	if (!cmds->args)
		return ;
	if (ft_strncmp(cmds->args->content, "pwd", 4) == 0)
		pwd_ms(shell, cmds->args, *list);
    else if (ft_strncmp(cmds->args->content, "echo", 5) == 0)
		echo_ms(cmds->args, shell);
	else if (ft_strncmp(cmds->args->content, "cd", 3) == 0)
		cd_ms(list, cmds->args, shell);
	else if (ft_strncmp(cmds->args->content, "env", 4) == 0)
		env_ms(*list, shell);
    else if (ft_strncmp(cmds->args->content, "exit", 5) == 0)
		exit_ms(shell, cmds->args);
	else if (ft_strncmp(cmds->args->content, "unset", 6) == 0)
		unset_ms(list, cmds->args, shell);
	else if (ft_strncmp(cmds->args->content, "export", 7) == 0)
		export_ms(list, cmds->args, shell);
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

int	handle_redirects(t_cmds *cmd, t_shell **shell, int in)
{
	int	i;

	i = 0;
	while (cmd->redirs && cmd->redirs[i])
	{
		open_files(cmd->redirs[i], shell, in);
		i++;
	}
	return (0);
}

void	execute_cmds(t_cmds **cmds, t_shell **shell, char **envp, char *line)
{
	int	in;
	int	out;
	envp = NULL;

	(*shell)->cmd_index = get_num_of_commands(cmds);
	if ((*shell)->cmd_index > 1)
		(*shell)->pipes = pipes_loop((*shell)->cmd_index);
	// printf("pipes: %d\n", (*shell)->pipes[0][0]);
	// printf("pipes: %d\n", (*shell)->pipes[0][1]);
	// printf("pipes: %d\n", (*shell)->pipes[1][0]);
	// printf("pipes: %d\n", (*shell)->pipes[1][1]);
	if (*line != '\0')
	{
		in = dup(STDIN_FILENO);
		out = dup(STDOUT_FILENO);
		if (is_built_in(cmds[0]->args->content) && !cmds[1])
		{
            // printf("aaaa\n");
			handle_redirects(cmds[0], shell, in);
			built_ins(&(cmds[0]->envs), cmds[0], shell, envp);
		}
		else
		{
			// printf("bbbb\n");
			execute_bin(cmds, shell, envp, in);
		}
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
	}
}