/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:59:15 by ocapers           #+#    #+#             */
/*   Updated: 2022/06/28 16:30:59 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_del2(t_cmds *cmd, t_list *args_copy)
{
	while (args_copy)
	{
		args_copy->content = quotes_del(args_copy->content, cmd);
		args_copy = args_copy->next;
	}
	return (0);
}

static t_cmds	*ft_command_new_part_two(t_cmds **cmd)
{
	int		i;

	i = -1;
	while ((*cmd)->redirs && (*cmd)->redirs[++i])
		(*cmd)->redirs[i]->name
			= quotes_del((*cmd)->redirs[i]->name, *cmd);
	quotes_del2(*cmd, (*cmd)->args);
	return (*cmd);
}

static t_cmds	*ft_command_new(char *str, t_envlist *envlist, t_shell *shell)
{
	t_cmds	*cmd;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	cmd = (t_cmds *)malloc(sizeof(t_cmds));
	if (!cmd)
		return (NULL);
	i = -1;
	j = -1;
	ft_memset(cmd, 0, sizeof(t_cmds));
	cmd->envlist = envlist;
	cmd->shell = shell;
	set_redirs(str, cmd);
	str = redirs_del(str);
	str = spaces_del(str);
	set_arguments(str, cmd);
	cmd = ft_command_new_part_two(&cmd);
	free(str);
	return (cmd);
}

int	set_cmd(char *str, t_cmds **cmds, t_envlist *envlist, t_shell *shell)
{
	int	i[5];

	ft_memset(i, 0, sizeof(int) * 5);
	i[0] = -1;
	while (str[++i[0]])
	{
		quotes_check(str[i[0]], &i[3], &i[4]);
		if (!i[3] && !i[4] && str[i[0]] == '|')
		{
			cmds[i[2]++] = ft_command_new(ft_substr(str,
						i[1], i[0] - i[1]), envlist, shell);
			if (!cmds[i[2] - 1])
				return (1);
			i[1] = i[0] + 1;
		}
	}
	cmds[i[2]++] = ft_command_new(ft_substr(str, i[1], i[0] - i[1]),
			envlist, shell);
	if (!cmds[i[2] - 1])
		return (1);
	cmds[i[2]] = NULL;
	return (0);
}

t_cmds	**parser(char *s, t_envlist *envlist, t_shell *shell)
{
	int		num_of_commands;
	t_cmds	**cmds;

	num_of_commands = check_str1(s) * check_str2(s);
	if (!num_of_commands)
	{
		ft_putstr_fd("minishell: error of parsing\n", 2);
		g_exit_status = 2;
		return (NULL);
	}
	cmds = (t_cmds **)malloc(sizeof(t_cmds *) * (num_of_commands + 1));
	if (!cmds)
		error("minishell: error of malloc\n");
	if (set_cmd(s, cmds, envlist, shell))
		clearing(&cmds);
	return (cmds);
}
