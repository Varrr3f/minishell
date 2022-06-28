#include "minishell.h"

void	ft_free_command_redirects(t_cmds *cmd)
{
	int	i;

	i = -1;
	while (cmd->redirs && cmd->redirs[++i])
	{
		free(cmd->redirs[i]->name);
		free(cmd->redirs[i]);
	}
	if (cmd->redirs)
		free(cmd->redirs);
}

int	ft_array_clear(char ***array)
{
	int	i;

	i = -1;
	if (!*array)
		return (1);
	while ((*array)[++i])
		free((*array)[i]);
	free(*array);
	*array = NULL;
	return (1);
}

void	clearing(t_cmds ***cmds)
{
	int	i;

	i = -1;
	if (!cmds || !(*cmds))
		return ;
	while (((*cmds)[++i]))
	{
		ft_free_command_redirects((*cmds)[i]);
		ft_lstclear(&(*cmds)[i]->args);
		free((*cmds)[i]);
	}
	free((*cmds));
	(*cmds) = NULL;
}
