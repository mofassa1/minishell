/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 23:06:29 by mezzine           #+#    #+#             */
/*   Updated: 2024/03/04 23:09:19 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_lstsize_strings(t_strings *lst)
{
	size_t		i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_strings	*ft_lstnew_strings(char *str, t_tokens t)
{
	t_strings	*n;

	n = ft_malloc(sizeof(t_strings), 'm');
	if (!n)
		return (NULL);
	n->str = str;
	n->type = t;
	n->next = NULL;
	return (n);
}

t_strings	*ft_lstlast_strings(t_strings *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_lstadd_back_strings(t_strings **lst, t_strings *new)
{
	t_strings	*last;

	if (lst)
	{
		if (!*lst)
		{
			*lst = new;
			return ;
		}
		last = ft_lstlast_strings(*lst);
		last->next = new;
	}
}
