#include "minishell.h"

void	quotes_check(char c, int *s_q, int *d_q)
{
	if (!*d_q && !*s_q && c == '\'')
		*s_q = 1;
	else if (!*d_q && !*s_q && c == '\"')
		*d_q = 1;
	else if (!*d_q && *s_q && c == '\'')
		*s_q = 0;
	else if (*d_q && !*s_q && c == '\"')
		*d_q = 0;
}

int	ft_check_first_command(char *str, int index)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (str[++i] && i < index)
		if (str[i] != ' ')
			j++;
	if (j)
		return (0);
	return (1);
}

int	check_str1(char *str)
{
	int		num_of_cmd;
	int		j[2];
	int		i;

	i = -1;
	ft_bzero(j, sizeof(int) * 2);
	num_of_cmd = 1;
	while (str && str[++i])
	{
		quotes_check(str[i], &j[0], &j[1]);
		if (!j[0] && !j[1] && (str[i] == '\\' || str[i] == ';'))
			return (0);
		else if (!j[0] && !j[1] && str[i] == '|')
			num_of_cmd++;
		if (!j[0] && !j[1] && str[i] == '|' && num_of_cmd == 2)
			if (ft_check_first_command(str, i))
				return (0);
	}
	if (!str || j[0] || j[1])
		return (0);
	return (num_of_cmd);
}

int	check_str2(char *str)
{
	int	q[2];
	int	i;
	int	j;
	int	ret;

	i = -1;
	ret = 1;
	ft_memset(q, 0, sizeof(int) * 2);
	while (str && str[++i])
	{
		quotes_check(str[i], &q[0], &q[1]);
		if (!q[0] && !q[1] && ft_strchr("<>|", str[i]))
		{
			if (str[i + 1] && ((str[i] == '>' && str[i + 1] == '>')
					|| (str[i] == '<' && str[i + 1] == '<')))
				i++;
			while (str[++i] && str[i] == ' ')
				;
			j = i;
			while (str[i] && !ft_strchr(" <>|", str[i]))
				i++;
			if (!(i - j))
				return (0);
		}
	}
	return (ret);
}
