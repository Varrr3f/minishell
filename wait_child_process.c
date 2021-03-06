#include "minishell.h"

void	get_child_exit_status(int *status)
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
			get_child_exit_status(&status);
			exit_status = status;
		}
		i++;
	}
}
