/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:59:20 by ocapers           #+#    #+#             */
/*   Updated: 2022/06/28 16:33:06 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_command(t_cmds *cmd, t_shell **shell, int in)
{
	dup2((*shell)->pipes[0][1], 1);
	redirs_do(cmd, in);
	close((*shell)->pipes[0][0]);
}

void	last_command(t_cmds *cmd, t_shell **shell, int in)
{
	redirs_do(cmd, in);
	dup2((*shell)->pipes[(*shell)->num_of_process - 2][0], 0);
	close((*shell)->pipes[(*shell)->num_of_process - 2][1]);
}

void	midl_command(t_shell **shell, int cmd_pos)
{
	dup2((*shell)->pipes[cmd_pos - 1][0], 0);
	dup2((*shell)->pipes[cmd_pos][1], 1);
}

void	get_cmd_pos(t_cmds *cmd, t_shell **shell, int cmd_pos, int in)
{
	if (cmd_pos == 0)
		first_command(cmd, shell, in);
	else if (cmd_pos == (*shell)->num_of_process - 1)
		last_command(cmd, shell, in);
	else
		midl_command(shell, cmd_pos);
}
