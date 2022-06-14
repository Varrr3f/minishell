#include "minishell.h"

void	close_all_pipes(int **pipes)
{
	int	i;

	i = 0;
	while (pipes && pipes[i])
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	open_pipes(int **pipes, int cmnds)
{
	int	i;

	i = 0;
	// printf("index: %d\n", cmnds);
	while (i < cmnds - 1)
	{
		if (pipe(pipes[i]) == -1)
			error("Error of pipe");;
		i++;
	}
}

int	**pipes_loop(int cmnds)
{
	int		i;
	int		**pipes;

	i = 0;
	pipes = (int **)malloc(sizeof(int *) * cmnds);
	if (!pipes)
		error("Error of malloc");
	while (i < cmnds - 1)
	{	
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			error("Error of malloc");;
		i++;
	}
	pipes[i] = NULL;
	open_pipes(pipes, cmnds);
	return (pipes);
}