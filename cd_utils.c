/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:57:31 by ocapers           #+#    #+#             */
/*   Updated: 2022/06/28 17:34:09 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_unset_home(void)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd("HOME not set\n", 2);
	g_exit_status = 1;
}

void	handle_empty_input(t_envlist *list)
{
	char		*root_path;
	int			status;

	root_path = find_envp(list, "HOME");
	status = chdir(root_path);
	if (status == -1)
		handle_unset_home();
}

void	handle_non_existing_path(t_list *args)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(args->next->content, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_exit_status = 1;
}
