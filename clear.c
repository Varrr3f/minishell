#include "minishell.h"

void	ft_free_command_redirects(t_cmds *command)
{
	int	i;

	i = -1;
	while (command->redirs && command->redirs[++i])
	{
		free(command->redirs[i]->word);
		free(command->redirs[i]);
	}
	if (command->redirs)
		free(command->redirs);
}

// int	ft_array_clear(char ***array)
// {
// 	int	i;

// 	i = -1;
// 	if (!*array)
// 		return (1);
// 	while ((*array)[++i])
// 		free((*array)[i]);
// 	free(*array);
// 	*array = NULL;
// 	return (1);
// }

void	commands_clear(t_cmds ***commands)
{
	int	i;

	i = -1;
	if (!commands || !(*commands))
		return ;
	while (((*commands)[++i]))
	{
		ft_free_command_redirects((*commands)[i]);
		ft_lstclear(&(*commands)[i]->args);
		free((*commands)[i]);
	}
	free((*commands));
	(*commands) = NULL;
}