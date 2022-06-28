#include "minishell.h"

void	sigquit_handler(int num)
{
	(void)num;
	write(1, "Quit: 3\n", 8);
	exit(3);
}

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
