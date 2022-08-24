/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ms.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:57:58 by ocapers           #+#    #+#             */
/*   Updated: 2022/06/28 16:59:30 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_ms(t_envlist *list)
{
	g_exit_status = 0;
	while (list)
	{
		write(1, list->key, ft_strlen(list->key));
		write(1, "=", 1);
		write(1, list->value, ft_strlen(list->value));
		write(1, "\n", 1);
		list = list->next;
	}
}
