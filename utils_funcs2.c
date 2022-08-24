/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_funcs2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:00:46 by ocapers           #+#    #+#             */
/*   Updated: 2022/06/28 16:00:47 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlist	*envp_add_init(char *key, char *value)
{
	t_envlist	*var;

	var = (t_envlist *)malloc(sizeof(t_envlist));
	if (!var)
		return (NULL);
	var->key = key;
	var->value = value;
	var->next = NULL;
	return (var);
}

void	envp_to_list_back(t_envlist **vars, t_envlist *new_var)
{
	t_envlist	*copy;

	copy = *vars;
	if (!(*vars))
	{
		new_var->next = *vars;
		*vars = new_var;
	}
	else
	{
		while (copy->next)
			copy = copy->next;
		copy->next = new_var;
		new_var->next = NULL;
	}
}

void	envp_to_list_del(t_envlist **vars, char *key)
{
	t_envlist	*curr;
	t_envlist	*prev;
	t_envlist	*next;

	if (!vars || !key)
		return ;
	curr = *vars;
	while (curr)
	{
		if (ft_strncmp(curr->key, key, ft_strlen(curr->key)) == 0)
		{
			next = curr->next;
			prev->next = next;
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	envlist_clear(t_envlist **vars)
{
	t_envlist	*prev;

	if (!(*vars))
		return ;
	prev = NULL;
	while (*vars)
	{
		prev = (*vars);
		(*vars) = (*vars)->next;
		if (prev)
		{
			free(prev->key);
			free(prev->value);
			free(prev);
		}
	}
	*vars = NULL;
}
