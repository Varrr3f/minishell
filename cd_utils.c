#include "minishell.h"

void	handle_unset_home(t_shell **shell)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd("HOME not set\n", 2);
	exit_status = 1;
}

void	handle_empty_input(t_envlist *list, t_shell **shell)
{
	char		*root_path;
	int			status;

	root_path = find_envp(list, "HOME");
	status = chdir(root_path);
	if (status == -1)
		handle_unset_home(shell);
}

void	handle_non_existing_path(t_list *args, t_shell **shell)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(args->next->content, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	exit_status = 1;
}
