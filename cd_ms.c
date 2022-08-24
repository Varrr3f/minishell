/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_ms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:57:24 by ocapers           #+#    #+#             */
/*   Updated: 2022/06/28 16:36:39 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_old_pwd_environ(t_envlist **list, char *old_path)
{
	t_envlist	*old_pwd_node;

	old_pwd_node = envp_add_init("OLD_PWD", ft_strdup(old_path));
	if (!old_pwd_node)
		error("minishell: error of malloc\n");
	envp_to_list_del(list, "OLD_PWD");
	envp_to_list_back(list, old_pwd_node);
}

void	change_new_pwd_environ(t_envlist **list, char *new_path)
{
	t_envlist	*new_pwd_node;

	new_pwd_node = envp_add_init("PWD", ft_strdup(new_path));
	if (!new_pwd_node)
		error("minishell: error of malloc\n");
	envp_to_list_del(list, "PWD");
	envp_to_list_back(list, new_pwd_node);
}

void	handle_cd_arguments(t_list *args, t_envlist *list)
{
	int		status;
	char	tmp_path[1024];

	status = 0;
	if (args->next && !ft_strncmp(args->next->content, "-", 1)
		&& ft_strlen(args->next->content) == 1)
	{
		if (find_envp(list, "OLD_PWD") == NULL)
		{
			ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
			g_exit_status = 1;
			return ;
		}
		else
		{
			status = chdir(find_envp(list, "OLD_PWD"));
			getcwd(tmp_path, 1024);
			ft_putstr_fd(tmp_path, 1);
			write(1, "\n", 1);
		}
	}
	else
		status = chdir(args->next->content);
	if (status == -1)
		handle_non_existing_path(args);
}

void	cd_ms(t_envlist **list, t_list *args)
{
	int		status;
	char	old_path[1024];
	char	new_path[1024];

	g_exit_status = 0;
	status = 0;
	getcwd(old_path, 1024);
	if (args->next == NULL)
		handle_empty_input(*list);
	else
		handle_cd_arguments(args, *list);
	if (getcwd(new_path, 1024) == NULL)
	{
		ft_putstr_fd("cd: error: no such file or directory\n", 2);
		return ;
	}
	change_new_pwd_environ(list, new_path);
	change_old_pwd_environ(list, old_path);
}
