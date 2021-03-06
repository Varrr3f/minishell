#include "minishell.h"

int	ft_is_n(char *potencial_flag)
{
	int	i;

	i = -1;
	while (potencial_flag[++i])
		if (potencial_flag[i] != 'n')
			return (1);
	return (0);
}

int	echo_side(t_list *curr)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (curr && ft_strncmp(curr->content, "-n", ft_strlen("-n")) == 0
		&& !ft_is_n(&(((char *)(curr->content))[1])))
	{
		flag = 1;
		curr = curr->next;
	}
	while (curr)
	{
		if (curr && curr->content && (((char *)curr->content)[0]) && i++)
			write(1, " ", 1);
		write(1, curr->content, ft_strlen(curr->content));
		curr = curr->next;
	}
	return (flag);
}

void	echo_ms(t_list *args, t_shell **shell)
{
	int		flag;
	t_list	*curr;

	curr = args->next;
	if (!curr && exit_status != 1)
	{
		write(1, "\n", 1);
		return ;
	}
	else if (!curr)
		return ;
	flag = echo_side(curr);
	if (!flag)
		write(1, "\n", 1);
	exit_status = 0;
}
