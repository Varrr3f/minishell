/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_ms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:58:20 by ocapers           #+#    #+#             */
/*   Updated: 2022/06/28 17:01:23 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**handle_export_without_args(t_envlist *list)
{
	int		size;
	char	**tmp;
	int		i;

	size = get_list_size(list);
	tmp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tmp)
		error("minishell: error of malloc\n");
	i = 0;
	while (list)
	{
		tmp[i] = ft_strjoin(list->key, "=", 0, 0);
		tmp[i] = ft_strjoin(tmp[i], list->value, 0, 0);
		if (tmp[i] == NULL)
			error("minishell: error of malloc\n");
		list = list->next;
		i++;
	}
	tmp[i] = NULL;
	tmp = get_sorted_keys(tmp, size);
	return (tmp);
}

void	display_sorted_list(char **sorted_keys)
{
	int	i;

	i = 0;
	while (sorted_keys[i] != NULL)
	{
		write(1, "declare -x ", 11);
		write(1, sorted_keys[i], ft_strlen(sorted_keys[i]));
		write(1, "\n", 1);
		i++;
	}
}

void	add_env_key_value_pair(t_envlist **list, char *arg)
{
	char		**key_value;
	t_envlist	*new_node;

	key_value = ft_split(arg, '=');
	if (!key_value)
		error("minishell: error of malloc\n");
	new_node = envp_add_init(key_value[0], key_value[1]);
	if (!new_node)
		error("minishell: error of malloc\n");
	envp_to_list_back(list, new_node);
	free(key_value);
}

void	handle_export_with_arguments(t_list *curr, t_envlist **list)
{
	while (curr)
	{
		if (!is_valid_env_key(curr->content))
		{
			g_exit_status = 1;
			write(2, "minishell: export: `", 20);
			write(2, curr->content, ft_strlen(curr->content));
			write(2, "': not a valid identifier\n", 27);
		}
		else if (!is_equal_sign(curr->content))
			g_exit_status = 0;
		else
		{	
			g_exit_status = 0;
			check_if_key_exists(list, curr->content);
			add_env_key_value_pair(list, curr->content);
		}
		curr = curr->next;
	}
}

void	export_ms(t_envlist **list, t_list *args)
{
	int		i;
	char	**sorted_keys;
	t_list	*curr;

	i = 1;
	sorted_keys = NULL;
	curr = args->next;
	if (!curr)
	{
		g_exit_status = 0;
		sorted_keys = handle_export_without_args(*list);
		display_sorted_list(sorted_keys);
	}
	else
		handle_export_with_arguments(curr, list);
}
