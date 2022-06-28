/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:47:52 by sdavos            #+#    #+#             */
/*   Updated: 2022/06/21 19:02:51 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*trash_dst;
	char	*ret;
	size_t	idk2;

	if (s == NULL)
		return (NULL);
	if (ft_strlen((char *)s) < start)
	{
		trash_dst = malloc(sizeof(char));
		trash_dst[0] = '\0';
		ret = trash_dst;
		return (trash_dst);
	}
	else
	{
		if (start + len > ft_strlen((char *)s))
			len = ft_strlen((char *)s) - start;
		trash_dst = malloc(sizeof(char) * len + 1);
		if (trash_dst == NULL)
			return (NULL);
		idk2 = -1;
		while (++idk2 < len)
			*(trash_dst + idk2) = *(s + start + idk2);
		*(trash_dst + idk2) = '\0';
		return (trash_dst);
	}
}