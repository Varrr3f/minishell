/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:47:52 by sdavos            #+#    #+#             */
/*   Updated: 2021/10/13 14:47:57 by sdavos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *buf, size_t n)
{
	unsigned char	*tmp_b;
	unsigned char	*tmp_d;
	size_t			i;

	i = 0;
	tmp_b = (unsigned char *)buf;
	tmp_d = (unsigned char *)dest;
	if ((tmp_b == NULL) && (tmp_d == NULL))
		return (NULL);
	if (tmp_b < tmp_d)
	{
		while (++i <= n)
			tmp_d[n - i] = tmp_b[n - i];
	}
	else
	{
		while (n-- > 0)
			*tmp_d++ = *tmp_b++;
	}
	return (dest);
}
