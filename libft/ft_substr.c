/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:47:52 by sdavos            #+#    #+#             */
/*   Updated: 2021/10/13 14:47:57 by sdavos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	f_len(unsigned int start, size_t str_len, size_t len)
{
	if (start > str_len)
		len = str_len;
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	str_len;
	char	*str;

	i = 0;
	j = 0;
	if (!s || len <= 0 || start >= ft_strlen((char *)s))
		return (ft_strdup(""));
	str_len = ft_strlen((char *)&s[start]);
	len = f_len(start, str_len, len);
	if (start == 0 && !(&s[start] == (const char *)&s))
		str = (char *)malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
	else
		str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
			str[j++] = s[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}
