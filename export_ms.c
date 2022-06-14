#include "minishell.h"

void	check_if_key_exists(t_envlist **list, char *arg)
{
	char	**key_value;
	char	*exists;

	key_value = ft_split(arg, '=');
	exists = find_env(*list, key_value[0]);
	if (exists)
		ft_envar_del_one(list, arg);
	free(key_value);
}

int	is_valid_env_key(char *token)
{
	int	i;

	i = 0;
	if (!ft_isalpha(token[i]) && token[i] != '_')
		return (0);
	i++;
	while (token[i] != '\0')
	{
		if (!ft_isascii(token[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_equal_sign(char *token)
{
	int	i;

	i = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	get_list_size(t_envlist *list)
{
	t_envlist	*tmp;
	int			size_of_list;

	tmp = list;
	size_of_list = 0;
	while (tmp != NULL)
	{
		size_of_list++;
		tmp = tmp->next;
	}
	return (size_of_list);
}

char	**get_sorted_keys(char **keys, int size_of_list)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < size_of_list)
	{
		j = 0;
		while (j < size_of_list - i - 1)
		{
			if (ft_strncmp(keys[j], keys[j + 1], ft_strlen(keys[j]) + 1) > 0)
			{
				tmp = keys[j];
				keys[j] = keys[j + 1];
				keys[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (keys);
}

char	**handle_export_without_args(t_envlist *list)
{
	int		size;
	char	**tmp;
	int		i;

	size = get_list_size(list);
	tmp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tmp)
		error("Error malloc\n");
	i = 0;
	while (list)
	{
		tmp[i] = ft_strjoin(list->key, "="); //чистить
		tmp[i] = ft_strjoin(tmp[i], list->value); //чистить
		if (tmp[i] == NULL)
			error("Error malloc\n");
		list = list->next;
		i++;
	}
	tmp[i] = NULL;
	tmp = get_sorted_keys(tmp, size);
	return (tmp);
}

void	display_sorted_list(char **sorted_keys)
{
	int	i;

	i = 0;
	while (sorted_keys[i] != NULL)
	{
		write(STDOUT_FILENO, "declare -x ", 11);
		write(STDOUT_FILENO, sorted_keys[i], ft_strlen(sorted_keys[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

void	add_env_key_value_pair(t_envlist **list, char *arg)
{
	char		**key_value;
	t_envlist	*new_node;

	key_value = ft_split(arg, '=');
	if (!key_value)
		error("Error malloc\n");
	new_node = ft_envar_new(key_value[0], key_value[1]);
	if (!new_node)
		error("Error malloc\n");
	ft_envar_add_back(list, new_node);
	free(key_value);
}

void	handle_export_with_arguments(t_list *curr, t_shell **shell, t_envlist **list)
{
	while (curr)
	{
		if (!is_valid_env_key(curr->content))
		{
			(*shell)->exit_status = 1;
			write(STDERR_FILENO, "minishell: export: `", 20);
			write(STDERR_FILENO, curr->content, ft_strlen(curr->content));
			write(STDERR_FILENO, "': not a valid identifier\n", 27);
		}
		else if (!is_equal_sign(curr->content))
			(*shell)->exit_status = 0;
		else
		{	
			(*shell)->exit_status = 0;
			check_if_key_exists(list, curr->content);
			add_env_key_value_pair(list, curr->content);
		}
		curr = curr->next;
	}
}

void	export_ms(t_envlist **list, t_list *args, t_shell **shell)
{
	char	**sorted_keys;
	t_list	*curr;

	sorted_keys = NULL;
	curr = args->next;
	if (!curr)
	{
		(*shell)->exit_status = 0;
		sorted_keys = handle_export_without_args(*list);
		display_sorted_list(sorted_keys);
	}
	else
		handle_export_with_arguments(curr, shell, list);
}