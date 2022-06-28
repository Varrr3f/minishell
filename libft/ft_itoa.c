/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:47:52 by sdavos            #+#    #+#             */
/*   Updated: 2021/10/13 14:47:57 by sdavos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ff_len(unsigned int n)
{
	unsigned int	i;

	i = 1;
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static unsigned int	f_minus(int n)
{
	unsigned int	nb;

	if (n < 0)
		nb = -n;
	else
		nb = n;
	return (nb);
}

static char	*mall(unsigned int len, int n)
{
	char	*dest;

	if (n < 0)
		dest = (char *)malloc(sizeof(char) * len + 2);
	else
		dest = (char *)malloc(sizeof(char) * len + 1);
	return (dest);
}

char	*ft_itoa(int n)
{
	char			*dest;
	unsigned int	nb;
	unsigned int	len;
	unsigned int	i;

	nb = f_minus(n);
	len = ff_len(nb);
	i = 0;
	dest = mall(len, n);
	if (dest == NULL)
		return (NULL);
	if (n < 0)
	{
		dest[i] = '-';
		len++;
	}
	i = len - 1;
	while (nb >= 10)
	{
		dest[i--] = nb % 10 + '0';
		nb = nb / 10;
	}
	dest[i] = nb % 10 + '0';
	dest[len] = '\0';
	return (dest);
}
