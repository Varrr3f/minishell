/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_funcs1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:00:41 by ocapers           #+#    #+#             */
/*   Updated: 2022/06/28 16:00:43 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

t_envlist	*envlist_key_value(char **envp)
{
	char		**key_value;
	t_envlist	*envlist;
	t_envlist	*var;
	int			i;

	envlist = NULL;
	if (!envp)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		key_value = ft_split(envp[i], '=');
		if (!key_value)
			error("minishell: error of malloc\n");
		var = envp_add_init(key_value[0], key_value[1]);
		if (!var)
			error("minishell: error of malloc\n");
		envp_to_list_back(&envlist, var);
		free(key_value);
	}
	return (envlist);
}

void	set_shell_level(t_envlist *envs, t_shell *shell)
{
	t_envlist	*tmp;

	tmp = envs;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "SHLVL", 5) == 0
			&& ft_strlen(tmp->key) == ft_strlen("SHLVL"))
			shell->shell_level = ft_atoi(tmp->value);
		tmp = tmp->next;
	}
}

char	*find_envp(t_envlist *list, const char *key)
{
	t_envlist	*tmp;
	char		*value;

	tmp = list;
	value = NULL;
	if (tmp == NULL)
		return (NULL);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0
			&& ft_strlen(tmp->key) == ft_strlen(key))
			value = tmp->value;
		tmp = tmp->next;
	}
	return (value);
}
