/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:59:00 by ocapers           #+#    #+#             */
/*   Updated: 2022/06/28 17:33:12 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_exec_help(t_cmds **cmds, t_shell **shell, char **envp)
{
	int	in;
	int	out;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	if (!cmds[1] && builtins_check(cmds[0]->args->content))
	{
		redirs_do(cmds[0], in);
		builtins_do(&(cmds[0]->envlist), cmds[0], envp);
	}
	else
		execve_in_pipes(cmds, shell, envp, in);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}

void	cmd_exec(t_cmds **cmds, t_shell **shell, char **envp, char *line)
{
	if (cmds && tabs_or_spaces(line) == false)
	{
		(*shell)->num_of_process = get_num_of_commands(cmds);
		if ((*shell)->num_of_process > 1)
			(*shell)->pipes = pipes_init((*shell)->num_of_process);
		if (*line != '\0')
			cmd_exec_help(cmds, shell, envp);
	}
}

char	*readline_sig(char *str)
{
	tty_hide_input();
	catch_signals();
	str = readline("minishell> ");
	if (!str)
	{
		write(2, "exit\n", 5);
		exit(1);
	}
	if (str && *str && *str != ' ')
		add_history(str);
	return (str);
}

void	reading_str(t_envlist **envlist, t_shell **shell, char **envp)
{
	char	*str;
	t_cmds	**cmds;

	str = NULL;
	(*shell)->pipes = NULL;
	cmds = NULL;
	rl_outstream = stderr;
	while (true)
	{
		str = readline_sig(str);
		cmds = parser(str, *envlist, *shell);
		cmd_exec(cmds, shell, envp, str);
		clearing(&cmds);
		free(str);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		*shell;
	t_envlist	*envlist;

	if (argc != 1)
		return (printf("Error: wrong number of arguments\n"));
	(void)argv;
	shell = NULL;
	envlist = NULL;
	envlist = (t_envlist *)malloc(sizeof(t_envlist));
	shell = (t_shell *)malloc(sizeof(t_shell));
	envlist = envlist_key_value(envp);
	set_shell_level(envlist, shell);
	g_exit_status = 0;
	reading_str(&envlist, &shell, envp);
	envlist_clear(&envlist);
	return (g_exit_status);
}
