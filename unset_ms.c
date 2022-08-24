/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_ms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:00:36 by ocapers           #+#    #+#             */
/*   Updated: 2022/06/28 17:02:41 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_env_name(const char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (false);
	str++;
	while (*str != '\0')
	{
		if (!ft_isalnum(*str) && *str != '+' && *str != '*' && *str != '_')
			return (false);
		str++;
	}
	return (true);
}

void	unset_ms(t_envlist **list, t_list *args)
{
	while (args)
	{
		if (is_valid_env_name(args->content) == false)
		{
			g_exit_status = 1;
			write(2, "minishell: unset: `", 19);
			write(2, args->content, ft_strlen(args->content));
			write(2, "': not a valid identifier\n", 27);
		}
		else
		{
			envp_to_list_del(list, args->content);
			g_exit_status = 0;
		}
		args = args->next;
	}
}
