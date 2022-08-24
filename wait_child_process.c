/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:00:51 by ocapers           #+#    #+#             */
/*   Updated: 2022/06/28 16:00:52 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_child_g_exit_status(int *status)
{
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		*status = WTERMSIG(*status);
	else if (WIFSTOPPED(*status))
		*status = WSTOPSIG(*status);
}

void	wait_child_pid(t_shell **shell, pid_t id)
{
	pid_t	process;
	int		status;
	int		i;

	status = 0;
	i = 0;
	while (i < (*shell)->num_of_process)
	{
		process = waitpid(-1, &status, 0);
		if (id == process)
		{
			get_child_g_exit_status(&status);
			g_exit_status = status;
		}
		i++;
	}
}
