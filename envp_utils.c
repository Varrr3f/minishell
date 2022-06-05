#include "minishell.h"

int set_level(t_envlist *envlist)
{
    t_envlist   *list;
    int         ret;

    list = envlist;
    while (list)
    {
        if (ft_strncmp(list->key, "SHLVL", 5) == 0)
            ret = ft_atoi(list->value);
        list = list->next;
    }
    return (ret);
}

t_envlist	*set_first_key_value(char *key, char *value)
{
	t_envlist	*ret;

	ret = (t_envlist *)malloc(sizeof(t_envlist));
	if (!ret)
		return (NULL);
	ret->key = key;
	ret->value = value;
	ret->next = NULL;
	return (ret);
}

void	set_key_value_list(t_envlist *first_two_elems, t_envlist **envlist)
{
	t_envlist	*buf;

	buf = *envlist;
	if (!(*envlist))
	{
		first_two_elems->next = *envlist;
		*envlist = first_two_elems;
	}
	else
	{
		while (buf->next)
			buf = buf->next;
		buf->next = first_two_elems;
		first_two_elems->next = NULL;
	}
}

t_envlist	*envp_to_envlist(char **envp)
{
	char		**key_value;
	int			i;
	t_envlist	*envlist;
	t_envlist	*first_two_elems;

	if (!envp)
		return (NULL);
	i = 0;
	envlist = NULL;
	while (envp[i])
	{
		key_value = ft_split(envp[i], '=');
		if (!key_value)
			error("Error of malloc\n");
		first_two_elems = set_first_key_value(key_value[0], key_value[1]);
		if (!first_two_elems)
			error("Error of malloc\n");
		set_key_value_list(first_two_elems, &envlist);
		free(key_value);
		i++;
	}
	return (envlist);
}