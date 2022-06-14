#include "minishell.h"

void	sig_heredoc(int sig)
{
	(void)sig;
	exit(1);
}

void	tty_input(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &term);
}

void	*sigint_handler(int sig_num)
{
	(void)sig_num;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return (NULL);
}

void	set_signals(void)
{
	signal(SIGINT, (void *)sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

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

void	set_signals_two(t_cmds **commands)
{
	if (ft_strncmp(commands[0]->args->content, "cat", ft_strlen("cat")) == 0)
		signal(SIGQUIT, (void *)sigquit_handler);
	signal(SIGINT, (void *)sig_fork);
	signal(SIGQUIT, sigquit_handler);
}

void	return_signals_parent_process(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}