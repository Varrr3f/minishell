/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:58:25 by ocapers           #+#    #+#             */
/*   Updated: 2022/06/28 15:58:27 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_if_key_exists(t_envlist **list, char *arg)
{
	char	**key_value;
	char	*exists;

	key_value = ft_split(arg, '=');
	exists = find_envp(*list, key_value[0]);
	if (exists)
		envp_to_list_del(list, arg);
	free(key_value);
}

int	is_valid_env_key(char *token)
{
	int	i;

	i = 0;
	if (!ft_isalpha(token[i]) && token[i] != '_')
		return (0);
	i++;
	while (token[i] != '\0')
	{
		if (!ft_isascii(token[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_equal_sign(char *token)
{
	int	i;

	i = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	get_list_size(t_envlist *list)
{
	t_envlist	*tmp;
	int			size_of_list;

	tmp = list;
	size_of_list = 0;
	while (tmp != NULL)
	{
		size_of_list++;
		tmp = tmp->next;
	}
	return (size_of_list);
}

char	**get_sorted_keys(char **keys, int size_of_list)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < size_of_list)
	{
		j = 0;
		while (j < size_of_list - i - 1)
		{
			if (ft_strncmp(keys[j], keys[j + 1], ft_strlen(keys[j]) + 1) > 0)
			{
				tmp = keys[j];
				keys[j] = keys[j + 1];
				keys[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (keys);
}
