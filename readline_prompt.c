#include "minishell.h"

bool	tabs_or_spaces(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}

int	get_num_of_commands(t_cmds **cmds)
{
	int	i;

	i = 0;
	while (cmds && cmds[i])
		i++;
	return (i);
}