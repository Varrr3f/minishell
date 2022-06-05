#include "minishell.h"

char	*del_spaces(char *str)
{
	char	*tmp;
	int		i[5];

	ft_memset(&i, 0, sizeof(int) * 5);
	tmp = NULL;
	while (str[i[0]])
	{
		quotes_check(&i[4], &i[3], str[i[0]]);
		if (!i[3] && !i[4] && str[i[0]] == ' ')
		{
			tmp = ft_substr(str, 0, i[0] + 1);
			i[1] = i[0];
			while (str[++i[0]] && str[i[0]] == ' ')
				;
			tmp = ft_strjoin(tmp, ft_strdup(&str[i[0]])); //зафришить начальные две строки
			free(str);
			i[0] = i[1];
			str = tmp;
		}
		i[0]++;
	}
	if (!tmp)
		return (str);
	return (tmp);
}

static void	go_through_redirects(char *str, int i[5])
{
	// printf("%s\n", str);
	if (str[(i[0])] && (str[i[0]] == '<' || str[i[0]] == '>'))
		(i[0])++;
	while (str[++(i[0])] && str[i[0]] == ' ')
		;
	while (str[(i[0])] && str[i[0]] != ' '
		&& str[i[0]] != '>' && str[i[0]] != '<')
	{
		quotes_check(&i[1], &i[2], str[i[0]]);
		if (i[1] || i[2])
		{
			while (i[1] || i[2])
			{
				i[0]++;
				quotes_check(&i[1], &i[2], str[i[0]]);
			}
		}
		i[0]++;
	}
}

char	*del_redirects(char *str)
{
	char	*tmp;
	int		i[5];

	// printf("%s\n", str);
	ft_memset(&i, 0, sizeof(int) * 5);
	tmp = NULL;
	while (str[i[0]])
	{
		quotes_check(&i[1], &i[2], str[i[0]]);
		if (!i[1] && !i[2] && (str[i[0]] == '<' || str[i[0]] == '>'))
		{
			tmp = ft_substr(str, 0, i[0]);
			// printf("%s\n", tmp);
			// printf("%d\n", i[0]);
			i[4] = i[0];
			go_through_redirects(str, i);
			// printf("%s\n", str);
			// printf("%s\n", ft_strdup(&str[i[0]]));
			tmp = ft_strjoin(tmp, ft_strdup(&str[i[0]])); //зафришить начальные две строки
			// printf("%s\n", tmp);
			free(str);
			i[0] = i[4];
			str = tmp;
			i[0]--;
		}
		i[0]++;
	}
	// printf("%s\n", tmp);
	if (!tmp)
		return (str);
	// printf("%s\n", str);
	return (tmp);
}

int	get_type_of_redir(char *str, int *i)
{
	if (str[*i] == '>' && str[*i + 1] != '>')
		return (0);
	else if (str[*i] == '<' && str[*i + 1] != '<')
		return (1);
	else if (str[*i] == '>' && str[*i + 1] == '>')
	{
		(*i)++;
		return (2);
	}
	else if (str[*i] == '<' && str[*i + 1] == '<')
	{
		(*i)++;
		return (3);
	}
	return (-1);
}

char *get_word_of_redir(char *str, int i[5])
{
	while (str[++i[0]] && str[i[0]] == ' ')
		;
	// printf("%d\n", i[0]);
	// printf("%d\n", i[1]);
	while (str[i[0] + i[4]] && !ft_strchr(" <>", str[i[0] + i[4]]))
	{
		quotes_check(&i[1], &i[2], str[i[0] + i[1]]);
		if (i[1] || i[2])
		{
			while (i[1] || i[2])
			{
				i[4]++;
				quotes_check(&i[1], &i[2], str[i[0] + i[4]]);
			}
		}
		i[4]++;
	}
	// printf("--%s\n", ft_substr(str, i[0], i[4]));
	return (ft_substr(str, i[0], i[4]));
}