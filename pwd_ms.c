/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_ms.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:59:29 by ocapers           #+#    #+#             */
/*   Updated: 2022/06/28 17:02:12 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_ms(t_list *args, t_envlist *list)
{
	char	dir[1024];
	char	*tmp_dir;

	if (args->next)
	{
		g_exit_status = 1;
		write(2, "pwd: too many arguments\n", 25);
	}
	else
	{
		g_exit_status = 0;
		if (getcwd(dir, 1024) == NULL)
		{
			tmp_dir = find_envp(list, "OLD_PWD");
			write(1, tmp_dir, ft_strlen(tmp_dir) + 1);
		}
		write(1, dir, ft_strlen(dir));
		write(1, "\n", 1);
	}
}
