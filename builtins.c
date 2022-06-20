#include "minishell.h"

void	env_ms(t_envlist *list, t_shell **shell)
{
	(*shell)->exit_status = 0;
	while (list)
	{
		write(STDOUT_FILENO, list->key, ft_strlen(list->key));
		write(STDOUT_FILENO, "=", 1);
		write(STDOUT_FILENO, list->value, ft_strlen(list->value));
		write(STDOUT_FILENO, "\n", 1);
		list = list->next;
	}
}

char	*find_env(t_envlist *list, const char *key)
{
	t_envlist	*tmp;
	char		*value;

	tmp = list;
	value = NULL;
	if (tmp == NULL)
		return (NULL);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen((char *)key)) == 0
			&& ft_strlen(tmp->key) == ft_strlen((char *)key))
			value = tmp->value;
		tmp = tmp->next;
	}
	return (value);
}

void	pwd_ms(t_shell **shell, t_list *args, t_envlist *list)
{
	char	dir[4096];
	char	*tmp_dir;

	if (args->next)
	{
		(*shell)->exit_status = 1;
		write(STDERR_FILENO, "pwd: too many arguments\n", 25);
	}
	else
	{
		(*shell)->exit_status = 0;
		if (getcwd(dir, 4096) == NULL)
		{
			tmp_dir = find_env(list, "OLDPWD");
			write(1, tmp_dir, ft_strlen(tmp_dir) + 1);
		}
		write(STDOUT_FILENO, dir, ft_strlen(dir));
		write(STDOUT_FILENO, "\n", 1);
	}
}

int	echo_help(t_list *curr)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (curr && ft_strncmp(curr->content, "-n", ft_strlen("-n")) == 0)
	{
		flag = 1;
		curr = curr->next;
	}
	while (curr)
	{
		if (curr && curr->content && (((char *)curr->content)[0]) && i++)
			write(STDOUT_FILENO, " ", 1);
		if ((((char *)curr->content)[0]) == '$')
		{
			write(STDOUT_FILENO, curr->next->content, (int)ft_strlen(curr->content));
			break;
		}
		// printf("content: %s\n", curr->content);
		// printf("len: %d\n", (int)ft_strlen(curr->content));
		write(STDOUT_FILENO, curr->content, (int)ft_strlen(curr->content));
		curr = curr->next;
	}
	return (flag);
}

void	echo_ms(t_list *args, t_shell **shell)
{
	int		flag;
	t_list	*curr;

	curr = args->next;
	if (!curr && (*shell)->exit_status != 1)
	{
		write(1, "\n", 1);
		return ;
	}
	else if (!curr)
		return ;
	flag = echo_help(curr);
	if (!flag)
		write(STDOUT_FILENO, "\n", 1);
	(*shell)->exit_status = 0;
}