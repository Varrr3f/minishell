#include "minishell.h"

bool	is_valid_env_name(const char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (false);
	str++;
	while (*str != '\0')
	{
		if (!ft_isalnum(*str) && *str != '+' && *str != '*' && *str != '_')
			return (false);
		str++;
	}
	return (true);
}

void	unset_ms(t_envlist **list, t_list *args, t_shell **shell)
{
	while (args)
	{
		if (is_valid_env_name(args->content) == false)
		{
			exit_status = 1;
			write(2, "minishell: unset: `", 19);
			write(2, args->content, ft_strlen(args->content));
			write(2, "': not a valid identifier\n", 27);
		}
		else
		{
			envp_to_list_del(list, args->content);
			exit_status = 0;
		}
		args = args->next;
	}
}
