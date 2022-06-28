#include "minishell.h"

void	handle_left_redir(t_redirs *elem, t_shell **shell)
{
	int	fd;

	fd = open(elem->name, O_RDONLY, 0777);
	if (fd == -1)
	{
		exit_status = 1;
		write(2, "minishell: ", 11);
		write(2, elem->name, ft_strlen(elem->name) + 1);
		write(2, ": No such file or directory\n", 28);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
}

void	handle_right_redir(t_redirs *elem, t_shell **shell)
{
	int	fd;

	fd = open(elem->name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
	{
		exit_status = 2;
		error("fd error\n");
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
		fd = open(elem->name, O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (fd == -1)
			error("fd error\n");
		dup2(fd, STDOUT_FILENO);
	}
	if (elem->type == 3)
	{
		signal(SIGINT, (void *)sig_heredoc);
		here_doc(elem->name, shell, in);
	}
}

int	redirs_do(t_cmds *cmd, t_shell **shell, int in)
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
