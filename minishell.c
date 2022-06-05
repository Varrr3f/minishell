#include "minishell.h"

void	error(char *error)
{
	ft_putstr_fd(error, 2);
	exit(1);
}

void	init_shell(t_shell *shell, t_envlist *envlist)
{
	shell->level = set_level(envlist);
	shell->exit_status = 0;
	shell->pipes = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_envlist	*envlist;
	t_shell		*shell;
	t_cmds		**cmds;
	char		*str;

	(void)argv;
	cmds = NULL;
	shell = malloc(sizeof(t_shell));
	envlist = envp_to_envlist(envp);
	init_shell(shell, envlist);
	rl_outstream = stderr;
	while (true)
	{
		tty_input();
		set_signals();
		str = readline("minishell> ");
		if (!str)
		{
			write(2, "exit\n", 5);
			exit(1);
		}
		if (str && *str && *str != ' ')
			add_history(str);
		cmds = parser(str, envlist, shell);
		execute_cmds(cmds, &shell, envp, str);
		//commands_clear(&cmds);
		free(str);
	}
	return (0);
}