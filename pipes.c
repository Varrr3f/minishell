/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:59:24 by ocapers           #+#    #+#             */
/*   Updated: 2022/06/28 15:59:26 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	open_pipes(int **pipes, int cmds)
{
	int	i;

	i = 0;
	while (i < cmds - 1)
	{
		if (pipe(pipes[i]) == -1)
			error("minishell: error of pipes\n");
		i++;
	}
}

int	**pipes_init(int cmds)
{
	int		i;
	int		**pipes;

	i = 0;
	pipes = (int **)malloc(sizeof(int *) * cmds);
	if (!pipes)
		error("minishell: error of malloc");
	while (i < cmds - 1)
	{	
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			error("minishell: error of malloc");
		i++;
	}
	pipes[i] = NULL;
	open_pipes(pipes, cmds);
	return (pipes);
}
