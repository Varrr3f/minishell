/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:47:52 by sdavos            #+#    #+#             */
/*   Updated: 2021/10/13 14:47:57 by sdavos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *buf, size_t n)
{
	unsigned char	*tmp_b;
	unsigned char	*tmp_d;

	tmp_b = (unsigned char *)buf;
	tmp_d = (unsigned char *)dest;
	if (n == 0 || dest == buf)
		return (dest);
	while (n--)
		*tmp_d++ = *tmp_b++;
	return (dest);
}
