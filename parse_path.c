/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocapers <ocapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:59:11 by ocapers           #+#    #+#             */
/*   Updated: 2022/06/28 15:59:13 by ocapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**parse_paths(t_envlist *list)
{
	char	**my_paths;	
	char	*path_env;
	int		i;

	i = 0;
	path_env = find_envp(list, "PATH");
	if (!path_env)
		return (NULL);
	my_paths = ft_split(path_env, ':');
	if (!my_paths)
		error("minishell: error of malloc");
	while (my_paths[i])
	{
		my_paths[i] = ft_strjoin(my_paths[i], "/", 0, 0);
		if (!my_paths[i])
			error("minishell: error of malloc");
		i++;
	}
	return (my_paths);
}

void	handle_no_path(char **path, char ***cmd_args)
{
	*path = ft_strjoin("/", (*cmd_args)[0], 0, 0);
	if (!*path)
		error("minishell: error of malloc");
	if (access(*path, F_OK))
		*path = NULL;
}

void	standart_bin(t_cmds *command, char **path, char ***cmd_args)
{
	char	**paths;
	int		i;

	i = 0;
	paths = parse_paths(command->envlist);
	*cmd_args = get_command_arguments(command->args);
	if (!(*cmd_args))
		error("minishell: error of malloc");
	while (paths && paths[i])
	{
		*path = ft_strjoin(paths[i], (*cmd_args)[0], 0, 0);
		if (!*path)
			error("minishell: error of malloc");
		if (access(*path, F_OK) == 0)
			break ;
		free(paths[i]);
		free(*path);
		*path = NULL;
		i++;
	}
	if (!*path)
		handle_no_path(path, cmd_args);
	free(paths);
}

void	path_bin(t_cmds *command, char **path, char ***cmdargs)
{
	*cmdargs = get_command_arguments(command->args);
	if (!*cmdargs)
		error("minishell: error of malloc");
	*path = (*cmdargs)[0];
}
