#include "minishell.h"

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

int	result(const char *str, unsigned long long res, int negative)
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

int	get_lvl(char *str, int negative)
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

void	exit_ms(t_shell **shell, t_list *args)
{
	write(STDERR_FILENO, "exit\n", 5);
	if (args->next)
	{
		if (get_args_quantity(args) != 2)
		{
			write(STDERR_FILENO, "minishell: exit: ", 17);
			write(STDERR_FILENO, args->content, ft_strlen(args->content));
			write(STDERR_FILENO, " too many arguments\n", 20);
			(*shell)->exit_status = 1;
		}
		else if (is_numeric(args->next->content) == false)
		{
			write(STDERR_FILENO, "minishell: exit: ", 17);
			write(STDERR_FILENO, args->next->content,
				ft_strlen(args->next->content));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			(*shell)->exit_status = 255;
			exit((*shell)->exit_status);
		}
		else if (is_numeric(args->next->content) == true)
			exit(get_lvl(args->next->content, 1));
	}
	exit((*shell)->exit_status);
}