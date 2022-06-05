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