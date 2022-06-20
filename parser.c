#include "minishell.h"

void	quotes_check(int *s_quote, int *d_quote, char ch)
{
	if (!*s_quote && !*d_quote && ch == '\'')
		*s_quote = 1;
	else if (!*s_quote && !*d_quote && ch == '\"')
		*d_quote = 1;
	else if (*s_quote && !*d_quote && ch == '\'')
		*s_quote = 0;
	else if (!*s_quote && *d_quote && ch == '\"')
		*d_quote = 0;
}

int get_count_cmds(char *str)
{
	int count;
	int quotes[2];
	int i;
	int j;
	int flag;

	i = 0;
	count = 1;
	ft_bzero(quotes, sizeof(int) * 2);
	while (str && str[i])
	{
		quotes_check(&quotes[0], &quotes[1], str[i]);
		if (!quotes[0] && !quotes[1] && (str[i] == '\\' || str[i] == ';'))
			return (0);
		else if (!quotes[0] && !quotes[1] && str[i] == '|')
			count++;
		if (!quotes[0] && !quotes[1] && str[i] == '|' && count == 2)
			if (str[i + 1] != ' ')
				return (0);
		i++;
	}
	if (!str || quotes[0] || quotes[1])
		return (0);
	i = 0;
	while (str && str[i])
	{
		if (!quotes[0] && !quotes[1] && ft_strchr("|<>", str[i]))
		{
			if (str[i + 1] && ((str[i] == '>' && str[i + 1] == '>')
					|| (str[i] == '<' && str[i + 1] == '<')))
				i++;
			// while (str[i] == ' ')
			// 	i++;
			while (str[++i] && str[i] == ' ')
				;
			j = i;
			while (str[i] && !ft_strchr(" <>|", str[i]))
				i++;
			flag = i - j;
			if (!flag)
				return (0);
		}
		i++;
	}
	return (count);
}

t_redirs	**get_redirs(char *str)
{
	int			i[3];
	t_redirs	**redirs_mass;
	int			redirs;

	ft_bzero(i, sizeof(int) * 3);
	redirs = 1;
	while (str[i[0]])
	{
		quotes_check(&i[1], &i[2], str[i[0]]);
		if (!i[1] && !i[2] && ft_strchr("<>", str[i[0]]))
		{
			redirs++;
			if (ft_strchr("<>", str[i[0] + 1]))
				i[0]++;
		}
		i[0]++;
	}
	redirs_mass = (t_redirs **)malloc(sizeof(t_redirs) * redirs);
	if (!redirs_mass)
		error("Error of malloc\n");
	ft_bzero(redirs_mass, sizeof(t_redirs *) * redirs);
	return (redirs_mass);
}

void	set_redirs_to_cmd(t_cmds *cmd, char *str)
{
	int	i[5];

	ft_bzero(i, sizeof(int) * 5);
	i[0] = -1;
	cmd->redirs = get_redirs(str);
	// printf("(()))%s\n", cmd->redirs[i[3]]->word);
	while (str[++i[0]] && cmd->redirs)
	{
		quotes_check(&i[1], &i[2], str[i[0]]);
		if (!i[1] && !i[2] && ft_strchr("<>", str[i[0]]))
		{
			i[4] = 0;
			// printf("%d\n", i[3]);
			cmd->redirs[i[3]] = (t_redirs *)malloc(sizeof(t_redirs));
			cmd->redirs[i[3]]->type = get_type_of_redir(str, &i[0]);
			cmd->redirs[i[3]]->word = get_word_of_redir(str, i);
			// printf("%d\n", i[3]);
			// printf("((%s\n", cmd->redirs[i[3]]->word);
			if (!cmd->redirs[i[3]]->word)
				error("Error of redir\n");
			i[0] = i[0] + i[4] - 1;
		}
		// i[0]++;
	}
	cmd->redirs[i[3]] = NULL;
}

t_cmds	*set_cmd(char *str, t_envlist *envlist, t_shell *shell)
{
	t_cmds *cmd;

	if (!str)
		return (NULL);
	cmd = (t_cmds *)malloc(sizeof(t_cmds));
	if (!cmd)
		return (NULL);
	ft_bzero(cmd, sizeof(t_cmds));
	cmd->envs = envlist;
	cmd->shell = shell;
	// printf("=%s=\n", str);
	set_redirs_to_cmd(cmd, str);
	str = del_redirects(str);
	// printf("=%s=\n", str);
	str = del_spaces(str);
	// printf("=%s=\n", str);
	get_cmd_arguments(str, cmd);
	// printf("[[%s\n", cmd->redirs[0]->word);
	cmd = get_cmd_two(&cmd);
	return (cmd);
}

t_cmds  **parser(char *str, t_envlist *envlist, t_shell *shell)
{
	t_cmds  **cmds;
	int     count_cmds;
	int		i[5];
	char	*pow;
	
	ft_bzero(i, sizeof(int) * 5);
	count_cmds = get_count_cmds(str);
	if (!count_cmds)
	{
		shell->exit_status = 2;
		ft_putstr_fd("error of cmdsss\n", 2);
		return (NULL);
	}
	cmds = (t_cmds **)malloc(sizeof(t_cmds *) * (count_cmds + 1));
	if (!cmds)
		error("Error of malloc\n");
	while (str[i[0]])
	{
		quotes_check(&i[1], &i[2], str[i[0]]);
		if (!i[1] && !i[2] && str[i[0]] == '|')
		{
			pow = ft_substr(str, i[4], i[0] - i[4]);
			cmds[i[3]++] = set_cmd(pow, envlist, shell);
			// printf("%s\n", cmds[i[3]]->redirs[0]->word);
			// if (!cmds[i[3] - 1])
			// 	commands_clear(&cmds);
			i[4] = i[0] + 1;
		}
		i[0]++;
	}
	cmds[i[3]++] = set_cmd(ft_substr(str, i[4], i[0] - i[4]), envlist, shell);
	// if (!cmds[i[3] - 1])
	// 	commands_clear(&cmds);
	cmds[i[3]] = NULL;
	// printf("%s\n", cmds[i[3]]->args->content);
	return (cmds);
}