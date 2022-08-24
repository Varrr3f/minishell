/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:58:54 by ocapers           #+#    #+#             */
/*   Updated: 2022/06/28 16:29:40 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *del, int in)
{
	char	*line;
	int		fd;

	g_exit_status = 0;
	fd = open("/tmp/file", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		error("fd error\n");
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
		error("fd error\n");
	dup2(fd, STDIN_FILENO);
}
