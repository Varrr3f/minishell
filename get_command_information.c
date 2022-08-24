/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_information.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:58:43 by ocapers           #+#    #+#             */
/*   Updated: 2022/06/28 15:58:45 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_filename(char *line, int i[5])
{
	while (line[++i[0]] && line[i[0]] == ' ')
		;
	while (line[i[0] + i[1]] && !ft_strchr(" <>", line[i[0] + i[1]]))
	{
		quotes_check(line[i[0] + i[1]], &i[3], &i[4]);
		if (i[3] || i[4])
		{
			while (i[3] || i[4])
			{
				i[1]++;
				quotes_check(line[i[0] + i[1]], &i[3], &i[4]);
			}
		}
		i[1]++;
	}
	return (ft_substr(line, i[0], i[1]));
}

static t_redirs	**ft_init_redirects(char *line)
{
	int			i;
	int			redirs;
	t_redirs	**redirs_arr;
	int			inside_s_quote;
	int			inside_d_quote;

	i = -1;
	redirs = 1;
	redirs_arr = NULL;
	inside_s_quote = 0;
	inside_d_quote = 0;
	while (line[++i])
	{
		quotes_check(line[i], &inside_s_quote, &inside_d_quote);
		if (!inside_d_quote && !inside_s_quote
			&& ft_strchr("<>", line[i]) && redirs++)
			if (ft_strchr("<>", line[i + 1]))
				i++;
	}
	redirs_arr = (t_redirs **)malloc(sizeof(t_redirs *) * redirs);
	if (!redirs_arr)
		error("minishell: error of malloc\n");
	ft_memset(redirs_arr, 0, sizeof(t_redirs *) * redirs);
	return (redirs_arr);
}

static int	ft_get_redirect_mode(char *line, int *i)
{
	if (line[*i] == '>' && line[*i + 1] != '>')
		return (0);
	else if (line[*i] == '<' && line[*i + 1] != '<')
		return (1);
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		(*i)++;
		return (2);
	}
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		(*i)++;
		return (3);
	}
	return (-1);
}

void	set_redirs(char *line, t_cmds *cmd)
{
	int	i[5];

	ft_memset(i, 0, sizeof(int) * 5);
	i[0] = -1;
	cmd->redirs = ft_init_redirects(line);
	while (cmd->redirs && line[++i[0]])
	{
		quotes_check(line[i[0]], &i[3], &i[4]);
		if (!i[3] && !i[4] && ft_strchr("<>", line[i[0]]))
		{
			i[1] = 0;
			cmd->redirs[i[2]] = (t_redirs *)malloc(sizeof(t_redirs));
			cmd->redirs[i[2]]->type = ft_get_redirect_mode(line, &i[0]);
			cmd->redirs[i[2]]->name = ft_get_filename(line, i);
			if (!cmd->redirs[i[2]++]->name)
				;
			i[0] += i[1] - 1;
		}
	}
	cmd->redirs[i[2]] = NULL;
}

void	set_arguments(char *line, t_cmds *cmd)
{
	t_list	*arg;
	int		i[5];

	ft_memset(i, 0, sizeof(int) * 5);
	i[0] = -1;
	while (line[++i[0]])
	{
		quotes_check(line[i[0]], &i[3], &i[4]);
		if (!i[0] && line[i[0]] == ' ' && !i[1]++)
			;
		if (i[0] && !i[3] && !i[4] && line[i[0]] == ' ')
		{
			if (!line[i[0] + 1])
				break ;
			arg = ft_lstnew(ft_substr(line, i[1], i[0] - i[1]));
			if (!arg)
				error("minishell: error of malloc\n");
			ft_lstadd_back(&cmd->args, arg);
			i[1] = i[0] + 1;
		}
	}
	arg = ft_lstnew(ft_substr(line, i[1], i[0] - i[1]));
	if (!arg)
		error("minishell: error of malloc\n");
	ft_lstadd_back(&cmd->args, arg);
}
