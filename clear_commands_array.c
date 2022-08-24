/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_commands_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:57:36 by ocapers           #+#    #+#             */
/*   Updated: 2022/06/28 15:57:39 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirects_clear(t_cmds *cmd)
{
	int	i;

	i = -1;
	while (cmd->redirs && cmd->redirs[++i])
	{
		free(cmd->redirs[i]->name);
		free(cmd->redirs[i]);
	}
	if (cmd->redirs)
		free(cmd->redirs);
}

int	array_clear(char ***array)
{
	int	i;

	i = -1;
	if (!*array)
		return (1);
	while ((*array)[++i])
		free((*array)[i]);
	free(*array);
	*array = NULL;
	return (1);
}

void	clearing(t_cmds ***cmds)
{
	int	i;

	i = -1;
	if (!cmds || !(*cmds))
		return ;
	while (((*cmds)[++i]))
	{
		redirects_clear((*cmds)[i]);
		ft_lstclear(&(*cmds)[i]->args);
		free((*cmds)[i]);
	}
	free((*cmds));
	(*cmds) = NULL;
}
