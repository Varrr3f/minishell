#include "minishell.h"

void	tty_hide_input(void)
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

void	catch_signals(void)
{
	signal(SIGINT, (void *)sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
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
