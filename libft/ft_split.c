/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:47:52 by sdavos            #+#    #+#             */
/*   Updated: 2021/10/13 14:47:57 by sdavos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	f_words(const char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			j++;
			while (str[i] != '\0' && str[i] != c)
				i++;
		}
	}
	return (j);
}

static char	*f_new_word(const char *str, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (*str && *str == c)
		str++;
	while (str[i] && str[i] != c)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	f_free(int i, char **ptr)
{
	while (i > 0)
	{
		free(ptr[i - 1]);
		i--;
	}
	free(ptr);
}

char	**ft_split(const char *str, char c)
{
	char	**ptr_word;
	int		i;
	int		words;

	if (!str)
		return (NULL);
	words = f_words(str, c);
	ptr_word = (char **)malloc(sizeof(char *) * (words + 1));
	if (ptr_word == NULL)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (*str && *str == c)
			str++;
		ptr_word[i] = f_new_word(str, c);
		if (ptr_word[i] == NULL)
			f_free(i, ptr_word);
		while (*str && *str != c)
			str++;
		i++;
	}
	ptr_word[i] = NULL;
	return (ptr_word);
}
