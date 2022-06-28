#include "minishell.h"

void	handle_first_command(t_cmds *cmd, t_shell **shell, int in)
{
	dup2((*shell)->pipes[0][1], STDOUT_FILENO);
	redirs_do(cmd, shell, in);
	close((*shell)->pipes[0][0]);
}

void	handle_last_command(t_cmds *cmd, t_shell **shell, int in)
{
	redirs_do(cmd, shell, in);
	dup2((*shell)->pipes[(*shell)->num_of_process - 2][0], STDIN_FILENO);
	close((*shell)->pipes[(*shell)->num_of_process - 2][1]);
}

void	handle_standard_command(t_shell **shell, int cmd_pos)
{
	dup2((*shell)->pipes[cmd_pos - 1][0], STDIN_FILENO);
	dup2((*shell)->pipes[cmd_pos][1], STDOUT_FILENO);
}

void	get_cmd_pos(t_cmds *cmd, t_shell **shell, int cmd_pos,
			int in)
{
	if (cmd_pos == 0)
		handle_first_command(cmd, shell, in);
	else if (cmd_pos == (*shell)->num_of_process - 1)
		handle_last_command(cmd, shell, in);
	else
		handle_standard_command(shell, cmd_pos);
}
