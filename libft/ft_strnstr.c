/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:47:52 by sdavos            #+#    #+#             */
/*   Updated: 2021/10/13 14:47:57 by sdavos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	str_len;
	char	*h;

	i = 0;
	h = (char *)haystack;
	str_len = ft_strlen((char *)needle);
	if (str_len == 0 || haystack == needle)
		return (h);
	while (h[i] != '\0' && i < len)
	{
		j = 0;
		while (h[i + j] != '\0' && needle[j] != '\0'
			&& h[i + j] == needle[j] && i + j < len)
			j++;
		if (j == str_len)
			return (h + i);
		i++;
	}
	return (0);
}
