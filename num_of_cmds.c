/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_of_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:59:06 by ocapers           #+#    #+#             */
/*   Updated: 2022/06/28 15:59:07 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	tabs_or_spaces(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}

int	get_num_of_commands(t_cmds **cmds)
{
	int	i;

	i = 0;
	while (cmds && cmds[i])
		i++;
	return (i);
}
