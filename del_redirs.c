/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_redirs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:57:42 by ocapers           #+#    #+#             */
/*   Updated: 2022/06/28 15:57:44 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirects_skip(char *str, int i[5])
{
	if (str[(i[0])] && (str[i[0]] == '<' || str[i[0]] == '>'))
		(i[0])++;
	while (str[++(i[0])] && str[i[0]] == ' ')
		;
	while (str[(i[0])] && str[i[0]] != ' '
		&& str[i[0]] != '>' && str[i[0]] != '<')
	{
		quotes_check(str[i[0]], &i[3], &i[4]);
		if (i[3] || i[4])
		{
			while (i[3] || i[4])
			{
				i[0]++;
				quotes_check(str[i[0]], &i[3], &i[4]);
			}
		}
		i[0]++;
	}
}

char	*redirs_del(char *str)
{
	char	*tmp;
	int		i[5];

	ft_memset(&i, 0, sizeof(int) * 5);
	tmp = NULL;
	while (str[i[0]])
	{
		quotes_check(str[i[0]], &i[3], &i[4]);
		if (!i[3] && !i[4] && (str[i[0]] == '<' || str[i[0]] == '>'))
		{
			tmp = ft_substr(str, 0, i[0]);
			i[1] = i[0];
			redirects_skip(str, i);
			tmp = ft_strjoin(tmp, ft_strdup(&str[i[0]]), 1, 1);
			free(str);
			i[0] = i[1];
			str = tmp;
			i[0]--;
		}
		i[0]++;
	}
	if (!tmp)
		return (str);
	return (tmp);
}

char	*spaces_del(char *str)
{
	char	*tmp;
	int		i[5];

	ft_memset(&i, 0, sizeof(int) * 5);
	tmp = NULL;
	while (str[i[0]])
	{
		quotes_check(str[i[0]], &i[4], &i[3]);
		if (!i[3] && !i[4] && str[i[0]] == ' ')
		{
			tmp = ft_substr(str, 0, i[0] + 1);
			i[1] = i[0];
			while (str[++i[0]] && str[i[0]] == ' ')
				;
			tmp = ft_strjoin(tmp, ft_strdup(&str[i[0]]), 1, 1);
			free(str);
			i[0] = i[1];
			str = tmp;
		}
		i[0]++;
	}
	if (!tmp)
		return (str);
	return (tmp);
}
