/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_del_q.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:58:30 by ocapers           #+#    #+#             */
/*   Updated: 2022/06/28 15:58:32 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	num_of_elems(char *str, int i, char **value, t_cmds *cmd)
{
	int	j;

	j = 1;
	if (str[i + 1] && ft_isdigit(str[i + 1]))
		j = 2;
	else if (str[i + 1] && str[i + 1] == '?')
	{
		if (cmd && cmd->shell)
				*value = ft_itoa(g_exit_status);
		j = 2;
	}
	else
		while (str[++i] && !ft_strchr("\'\"$ =", str[i]))
			j++;
	return (j);
}

char	*change_path(char *str, int *index, t_cmds *cmd)
{
	char		*value;
	t_envlist	*envlist;
	int			i;

	i = *index;
	value = NULL;
	envlist = cmd->envlist;
	i += num_of_elems(str, i, &value, cmd);
	while (!value && envlist)
	{
		if (!ft_strncmp(&str[*index + 1], envlist->key, i - *index - 1)
			&& (i - *index - 1) == (int)ft_strlen(envlist->key))
			value = ft_strdup(envlist->value);
		envlist = envlist->next;
	}
	if (!value && (i - *index - 1))
		value = ft_strdup("");
	else if (!value && !(i - *index - 1))
		value = ft_strdup("$");
	value = ft_strjoin(ft_substr(str, 0, *index), value, 1, 1);
	*index = ft_strlen(value) - 1;
	value = ft_strjoin(value, ft_strdup(&str[i]), 1, 1);
	free(str);
	return (value);
}

char	*quotes_del(char *str, t_cmds *cmd)
{
	int	i;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '\'')
			str = quot_skip(str, &i, '\'', cmd);
		else if (str[i] == '\"')
			str = quot_skip(str, &i, '\"', cmd);
		else if (str[i] == '$')
			str = change_path(str, &i, cmd);
	}
	return (str);
}
