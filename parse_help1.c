#include "minishell.h"

int	get_delta_of_indexes(char *str, int i, char **value, t_cmds *cmd)
{
	int	j;

	j = 1;
	if (str[i + 1] && ft_isdigit(str[i + 1]))
		j = 2;
	else if (str[i + 1] && str[i + 1] == '?')
	{
		if (cmd && cmd->shell)
				*value = ft_itoa(cmd->shell->exit_status);
		j = 2;
	}
	else
		while (str[++i] && !ft_strchr("\'\"$ =", str[i]))
			j++;
	// printf("j = %d\n", j);
	return (j);
}

char	*replace_path(char *str, int *index, t_cmds *cmd)
{
	char		*value;
	t_envlist	*env;
	int			i;

	i = *index; //1
	value = NULL;
	env = cmd->envs;
	// printf("%d\n", i);
	i += get_delta_of_indexes(str, i, &value, cmd); //5
	while (!value && env)
	{
		if (!ft_strncmp(&str[*index + 1], env->key, i - *index - 1)
			&& (i - *index - 1) == (int)ft_strlen(env->key))
		{
			value = ft_strdup(env->value);
			// printf("%s\n", value);
		}
		env = env->next;
	}
	if (!value && (i - *index - 1)) //5-1-1=3
	{
		value = ft_strdup("");
		// printf("%s\n", value);
	}
	else if (!value && !(i - *index - 1))
		value = ft_strdup("$");
	// printf("%s\n", value);
	value = ft_strjoin(ft_substr(str, 0, *index), value); //отчистить
	// printf("%s\n", value);
	*index = ft_strlen(value) - 1;
	value = ft_strjoin(value, ft_strdup(&str[i])); //отчистить
	free(str);
    // printf("%s\n", value);
	return (value);
}

char	*strip_quotes(char *str, int *index, char quote, t_cmds *cmd)
{
	int		i;
	char	*tmp[3];

	i = *index + 1;
	// printf("%s\n", str);
	// printf("%d\n", i);
	// printf("%d\n", *index);
	while (str[i] && str[i] != quote)
	{
		if (str[i] == '$' && quote != '\'')
        {
			str = replace_path(str, &i, cmd); //str, i = 1, cmd
			// printf("%s\n", str);
        }
		i++;
	}
	if (i - *index > 1)
	{
		// printf("ttt\n");
		tmp[0] = ft_substr(str, 0, *index);
		// printf("%s\n", tmp[0]);
		tmp[1] = ft_substr(str, *index + 1, i - *index - 1);
		tmp[2] = ft_strdup(&str[i + 1]);
		*index = ft_strlen(tmp[0]) + ft_strlen(tmp[1]) - 1;
	}
	else
	{
		// printf("ttt\n");
		tmp[0] = ft_substr(str, 0, *index);
		*index = ft_strlen(tmp[0]) - 1;
		tmp[1] = ft_strdup(&str[i + 1]);
		tmp[2] = NULL;
	}
	tmp[0] = ft_strjoin(tmp[0], tmp[1]); //отчистить tmp0 tmp1
	tmp[0] = ft_strjoin(tmp[0], tmp[2]); //отчистить tmp0 tmp2
	free(str);
	// printf("=%s=\n", tmp[0]);
	return (tmp[0]);
}

char	*del_quotes(char *str, t_cmds *cmd)
{
	int	i;

	i = -1;
	// printf("%s\n", str);
	while (str && str[++i])
	{
		// printf("uuu\n");
		if (str[i] == '\'')
			str = strip_quotes(str, &i, '\'', cmd);
		else if (str[i] == '\"')
		{
			// printf("yes\n");
			// printf("%s\n", str);
			str = strip_quotes(str, &i, '\"', cmd);
		}
		else if (str[i] == '$')
			str = replace_path(str, &i, cmd);
	}
	// printf("%s\n", str);
	return (str);
}

t_cmds	*get_cmd_two(t_cmds **cmd)
{
	int		i;

	i = -1;
    // printf("==%s\n", (*cmd)->redirs[0]->word);
	while ((*cmd)->redirs && (*cmd)->redirs[++i])
    {
        // printf("%s\n", (*cmd)->redirs[i]->word);
		// printf("uuu\n");
		(*cmd)->redirs[i]->word = del_quotes((*cmd)->redirs[i]->word, *cmd);
    }
	return (*cmd);
}

void	get_cmd_arguments(char *str, t_cmds *cmd)
{
	t_list	*arg;
	int		i[5];
    char    *sub;

	ft_memset(i, 0, sizeof(int) * 5);
    // printf("%s=\n", str);
	while (str[i[0]])
	{
		quotes_check(&i[3], &i[4], str[i[0]]);
		if (!i[0] && str[i[0]] == ' ' && !i[1]++)
			;
        // printf("%d\n", i[1]);
		if (i[0] && !i[3] && !i[4] && str[i[0]] == ' ')
		{
			if (!str[i[0] + 1])
            {
                // printf("aaaa\n");
				break ;
            }
			arg = ft_lstnew(ft_substr(str, i[1], i[0] - i[1]));
			if (!arg)
				error("Error (list cmd)\n");
			ft_lstadd_back(&cmd->args, arg);
			i[1] = i[0] + 1;
		}
        i[0]++;
	}
    // printf("i0 = %d\n", i[0]);
    // printf("%d\n", i[0] - i[1]);
    sub = ft_substr(str, i[1], i[0] - i[1]);
    // printf("sub = %s=\n", sub);
	arg = ft_lstnew(sub);
	if (!arg)
		error("Error (list cmd)\n");
	ft_lstadd_back(&cmd->args, arg);
	// printf("(%s)\n", cmd->args->content);
}
