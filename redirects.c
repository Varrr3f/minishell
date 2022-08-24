/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:00:19 by ocapers           #+#    #+#             */
/*   Updated: 2022/06/28 16:32:34 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	left_redir(t_redirs *elem)
{
	int	fd;

	fd = open(elem->name, O_RDONLY, 0777);
	if (fd == -1)
	{
		g_exit_status = 1;
		write(2, "minishell: ", 11);
		write(2, elem->name, ft_strlen(elem->name) + 1);
		write(2, ": No such file or directory\n", 28);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
}

void	right_redir(t_redirs *elem)
{
	int	fd;

	fd = open(elem->name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
	{
		g_exit_status = 2;
		error("fd error\n");
	}
	dup2(fd, STDOUT_FILENO);
}

void	open_files(t_redirs *elem, int in)
{	
	int	fd;

	if (elem->type == 0)
		right_redir(elem);
	if (elem->type == 1)
		left_redir(elem);
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
		here_doc(elem->name, in);
	}
}

int	redirs_do(t_cmds *cmd, int in)
{
	int	i;

	i = 0;
	while (cmd->redirs && cmd->redirs[i])
	{
		open_files(cmd->redirs[i], in);
		i++;
	}
	return (0);
}
