#include "minishell.h"

void	env_ms(t_envlist *list, t_shell **shell)
{
	exit_status = 0;
	while (list)
	{
		write(1, list->key, ft_strlen(list->key));
		write(1, "=", 1);
		write(1, list->value, ft_strlen(list->value));
		write(1, "\n", 1);
		list = list->next;
	}
}
