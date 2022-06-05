/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:47:52 by sdavos            #+#    #+#             */
/*   Updated: 2021/10/13 14:47:57 by sdavos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	f_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		s;
	int		end;

	s = 0;
	if (!s1)
		return (NULL);
	while (s1[s] && f_set(s1[s], set))
		s++;
	end = ft_strlen((char *)s1);
	while (end > s && f_set(s1[end - 1], set))
		end--;
	str = (char *)malloc(sizeof(char) * (end - s + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s < end)
		str[i++] = s1[s++];
	str[i] = '\0';
	return (str);
}
