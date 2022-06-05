
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*copy;

	copy = *lst;
	if (!*lst)
		ft_lstadd_front(lst, new);
	else
	{
		while (copy->next)
			copy = copy->next;
		copy->next = new;
	}
}
