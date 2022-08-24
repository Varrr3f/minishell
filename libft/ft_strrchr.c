/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:47:52 by sdavos            #+#    #+#             */
/*   Updated: 2021/10/13 14:47:57 by sdavos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*ret;
	int		last;

	last = ft_strlen((char *)str);
	ret = NULL;
	if (c >= 256)
		c = c - 256;
	while (last != 0)
	{
		if (str[last] == c)
		{
			ret = (char *)&str[last];
			return (ret);
		}
		last--;
	}
	if (str[0] == c)
		return ((char *)str);
	return (ret);
}
