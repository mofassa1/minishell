/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:29:26 by mezzine           #+#    #+#             */
/*   Updated: 2024/03/05 17:07:18 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*ft_lstnew_parser(void)
{
	t_parser	*n;

	n = ft_malloc(sizeof(t_parser), 'm');
	if (!n)
		return (NULL);
	n->cmd = NULL;
	n->flags = NULL;
	n->infile = NULL;
	n->outfile = NULL;
	n->next = NULL;
	n->prev = NULL;
	return (n);
}

t_parser	*ft_lstlast__parser(t_parser *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_lstadd_back_parser(t_parser **lst, t_parser *new)
{
	t_parser	*last;

	if (lst)
	{
		if (!*lst)
		{
			*lst = new;
			return ;
		}
		last = ft_lstlast__parser(*lst);
		last->next = new;
		new->prev = last;
	}
}
