/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:58:14 by ocapers           #+#    #+#             */
/*   Updated: 2022/06/28 17:00:03 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	num_of_list_elems(t_list *args)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = args;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

bool	is_numeric(const char *str)
{
	if (*str == '-')
		str++;
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (false);
		str++;
	}
	return (true);
}

static int	result(const char *str, unsigned long long res, int negative)
{
	int					i;
	unsigned long long	long_num;

	long_num = 9223372036854775807;
	long_num++;
	i = 0;
	while (!(*str >= '0' && *str <= '9'))
		str++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if ((res > 9223372036854775807 && negative == 1) \
		|| (res > long_num && negative == -1) || i > 19)
		return (255);
	return (res * negative);
}

static int	get_lvl(char *str, int negative)
{
	unsigned long long	ret;
	char				*tmp;

	ret = 0;
	tmp = str;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-')
	{
		negative = -negative;
		str++;
	}
	else if (*str == '+')
		str++;
	if (*str < '0' || *str > '9')
		return (255);
	while (*str >= '0' && *str <= '9')
	{
		ret = ret * 10 + *str - '0';
		str++;
	}
	if (*str == '\0')
		return (result(tmp, ret, negative));
	else
		return (255);
}

void	exit_ms(t_list *args)
{
	ft_putstr_fd("exit\n", 2);
	if (args->next)
	{
		if (num_of_list_elems(args) != 2)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args->content, 2);
			ft_putstr_fd(" too many arguments\n", 2);
			g_exit_status = 1;
		}
		else if (is_numeric(args->next->content) == false)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args->next->content, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			g_exit_status = 255;
			exit(g_exit_status);
		}
		else if (is_numeric(args->next->content) == true)
			exit(get_lvl(args->next->content, 1));
	}
	exit(g_exit_status);
}
