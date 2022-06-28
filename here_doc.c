#include "minishell.h"

void	here_doc(char *del, t_shell **shell, int in)
{
	char	*line;
	int		fd;

	exit_status = 0;
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
