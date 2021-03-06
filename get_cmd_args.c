#include "minishell.h"

char	**get_command_arguments(t_list *args)
{
	t_list	*curr;
	char	**cmd_args;
	int		j;
	int		i;

	i = 0;
	curr = args;
	j = num_of_list_elems(args);
	cmd_args = (char **)malloc(sizeof(char *) * (j + 1));
	if (!cmd_args)
		error("minishell: error of malloc\n");
	while (i < j)
	{
		cmd_args[i] = ft_strdup(curr->content);
		if (!cmd_args[i])
			error("minishell: error of malloc\n");
		curr = curr->next;
		i++;
	}
	cmd_args[i] = NULL;
	return (cmd_args);
}
