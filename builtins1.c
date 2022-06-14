#include "minishell.h"

void	handle_unset_home(t_shell **shell)
{
	write(STDERR_FILENO, "minishell: cd: ", 15);
	write(STDERR_FILENO, "HOME not set\n", 14);
	(*shell)->exit_status = 1;
}

void	handle_empty_input(t_envlist *list, t_shell **shell)
{
	char		*root_path;
	int			status;

	root_path = find_env(list, "HOME");
	status = chdir(root_path);
	if (status == -1)
		handle_unset_home(shell);
}

void	handle_non_existing_path(t_list *args, t_shell **shell)
{
	write(STDERR_FILENO, "minishell: cd: ", 15);
	write(STDERR_FILENO, args->next->content, ft_strlen(args->next->content));
	write(STDERR_FILENO, ": No such file or directory\n", 29);
	(*shell)->exit_status = 1;
}

void	ft_envar_del_one(t_envlist **vars, char *key)
{
	t_envlist	*curr;
	t_envlist	*prev;
	t_envlist	*next;

	if (!vars || !key)
		return ;
	curr = *vars;
	while (curr)
	{
		if (ft_strncmp(curr->key, key, ft_strlen(curr->key)) == 0)
		{
			next = curr->next;
			prev->next = next;
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	ft_envar_add_back(t_envlist **vars, t_envlist *new_var)
{
	t_envlist	*copy;

	copy = *vars;
	if (!(*vars))
	{
		new_var->next = *vars;
		*vars = new_var;
	}
	else
	{
		while (copy->next)
			copy = copy->next;
		copy->next = new_var;
		new_var->next = NULL;
	}
}

t_envlist	*ft_envar_new(char *key, char *value)
{
	t_envlist	*var;

	var = (t_envlist *)malloc(sizeof(t_envlist));
	if (!var)
		return (NULL);
	var->key = key;
	var->value = value;
	var->next = NULL;
	return (var);
}

void	change_old_pwd_environ(t_envlist **list, char *old_path)
{
	t_envlist	*old_pwd_node;

	old_pwd_node = set_first_key_value("OLD_PWD", ft_strdup(old_path));
	if (!old_pwd_node)
		error("Malloc Error\n");
	ft_envar_del_one(list, "OLD_PWD");
	ft_envar_add_back(list, old_pwd_node);
}

void	change_new_pwd_environ(t_envlist **list, char *new_path)
{
	t_envlist	*new_pwd_node;
	// t_envlist	*tmp;

	// tmp = *list;
	new_pwd_node = ft_envar_new("PWD", ft_strdup(new_path));
	if (!new_pwd_node)
		error("Malloc Error\n");
	ft_envar_del_one(list, "PWD");
	ft_envar_add_back(list, new_pwd_node);
}

void	handle_cd_arguments(t_list *args, t_shell **shell, t_envlist *list)
{
	int		status;
	char	tmp_path[4096];

	status = 0;
	if (args->next && !ft_strncmp(args->next->content, "-", 1)
		&& ft_strlen(args->next->content) == 1)
	{
		if (find_env(list, "OLD_PWD") == NULL)
		{
			write(STDERR_FILENO, "bash: cd: OLDPWD not set\n", 25);
			(*shell)->exit_status = 1;
			return ;
		}
		else
		{
			status = chdir(find_env(list, "OLD_PWD"));
			getcwd(tmp_path, 4096);
			write(STDOUT_FILENO, tmp_path, ft_strlen(tmp_path) + 1);
			write(1, "\n", 1);
		}
	}
	else
		status = chdir(args->next->content);
	if (status == -1)
		handle_non_existing_path(args, shell);
}

void	cd_ms(t_envlist **list, t_list *args, t_shell **shell)
{
	// int		status;
	char	old_path[4096];
	char	new_path[4096];

	(*shell)->exit_status = 0;
	// status = 0;
	getcwd(old_path, 4096);
	if (args->next == NULL)
		handle_empty_input(*list, shell);
	else
		handle_cd_arguments(args, shell, *list);
	if (getcwd(new_path, 4096) == NULL)
	{
		write(STDERR_FILENO, "cd Error\n", 10);
		return ;
	}
	change_new_pwd_environ(list, new_path);
	change_old_pwd_environ(list, old_path);
}
