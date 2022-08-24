/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:00:26 by ocapers           #+#    #+#             */
/*   Updated: 2022/06/28 16:00:28 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*sig_fork(int num)
{
	(void)num;
	exit(2);
}

void	set_signals(t_cmds **cmds)
{
	if (ft_strncmp(cmds[0]->args->content, "cat", ft_strlen("cat")) == 0)
		signal(SIGQUIT, (void *)sigquit_handler);
	signal(SIGINT, (void *)sig_fork);
	signal(SIGQUIT, sigquit_handler);
}

void	return_signals_parent_process(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_heredoc(int sig)
{
	(void)sig;
	exit(1);
}

void	c_fork(int signum)
{
	(void)signum;
	write(1, "\n", 1);
}
