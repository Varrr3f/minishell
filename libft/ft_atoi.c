/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:47:52 by sdavos            #+#    #+#             */
/*   Updated: 2021/10/13 14:47:57 by sdavos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	result(long res)
{
	if (res < -2147483648)
		return (0);
	if (res > 2147483647)
		return (-1);
	return (res);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		time;
	long	num;
	int		minus;

	i = 0;
	num = 0;
	minus = 1;
	time = 0;
	while (str[i] == '\t' || str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == '\n' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			minus = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i++] - '0';
		if (++time == 18)
			break ;
	}
	return (result(num * minus));
}
