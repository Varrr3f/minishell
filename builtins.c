#include "minishell.h"

int	builtins_check(char *cmd)
{
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	return (0);
}

char	*quot_skip(char *str, int *index, char quote, t_cmds *cmd)
{
	int		i;
	char	*tmp[3];

	i = *index;
	while (str[++i] && str[i] != quote)
		if (str[i] == '$' && quote != '\'')
			str = change_path(str, &i, cmd);
	if (i - *index > 1)
	{
		tmp[0] = ft_substr(str, 0, *index);
		tmp[1] = ft_substr(str, *index + 1, i - *index - 1);
		tmp[2] = ft_strdup(&str[i + 1]);
		*index = ft_strlen(tmp[0]) + ft_strlen(tmp[1]) - 1;
	}
	else
	{
		tmp[0] = ft_substr(str, 0, *index);
		*index = ft_strlen(tmp[0]) - 1;
		tmp[1] = ft_strdup(&str[i + 1]);
		tmp[2] = NULL;
	}
	tmp[0] = ft_strjoin(tmp[0], tmp[1], 1, 1);
	tmp[0] = ft_strjoin(tmp[0], tmp[2], 1, 1);
	free(str);
	return (tmp[0]);
}

void	builtins_do(t_envlist **list, t_cmds *cmd, t_shell **shell,
			char **envp)
{
	(void)envp;
	if (!cmd->args)
		return ;
	if (ft_strncmp(cmd->args->content, "pwd", 4) == 0)
		pwd_ms(shell, cmd->args, *list);
	else if (ft_strncmp(cmd->args->content, "cd", 3) == 0)
		cd_ms(list, cmd->args, shell);
	else if (ft_strncmp(cmd->args->content, "echo", 5) == 0)
		echo_ms(cmd->args, shell);
	else if (ft_strncmp(cmd->args->content, "export", 7) == 0)
		export_ms(list, cmd->args, shell);
	else if (ft_strncmp(cmd->args->content, "env", 4) == 0)
		env_ms(*list, shell);
	else if (ft_strncmp(cmd->args->content, "unset", 6) == 0)
		unset_ms(list, cmd->args, shell);
	else if (ft_strncmp(cmd->args->content, "exit", 5) == 0)
		exit_ms(shell, cmd->args);
}
