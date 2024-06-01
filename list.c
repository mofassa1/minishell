/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:45:48 by mezzine           #+#    #+#             */
/*   Updated: 2024/04/02 04:38:56 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*dup_lexer_node(t_lexer *node)
{
	return (ft_lstnew(node->str, node->token));
}

t_lexer	*lexer_copy(t_lexer *h, t_lexer *limite)
{
	t_lexer	*new_h;

	new_h = NULL;
	while (h && h != limite)
	{
		ft_lstadd_back(&new_h, dup_lexer_node(h));
		h = h->next;
	}
	return (new_h);
}

t_lexer	*ft_lstnew(char *word, t_tokens t)
{
	t_lexer	*n;

	n = ft_malloc(sizeof(t_lexer), 'm');
	if (!n)
		return (NULL);
	n->str = word;
	n->token = t;
	n->ori5inal = word;
	n->next = NULL;
	n->prev = NULL;
	return (n);
}

t_lexer	*ft_lstlast(t_lexer *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_lstadd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*last;

	if (lst && new)
	{
		if (!*lst)
		{
			*lst = new;
			return ;
		}
		last = ft_lstlast(*lst);
		last->next = new;
		new->prev = last;
	}
}
