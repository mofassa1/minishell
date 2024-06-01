/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expande_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 03:41:02 by mezzine           #+#    #+#             */
/*   Updated: 2024/04/03 07:06:27 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*new_nodes_lexer(char *s, t_tokens type)
{
	char	**str;
	t_lexer	*new;

	str = ft_split(s, " \n\t\v\r");
	new = NULL;
	while (*str)
	{
		ft_lstadd_back(&new, ft_lstnew(*str, type));
		str++;
	}
	return (new);
}

t_lexer	*expande_list(t_lexer *h)
{
	t_lexer	*new;

	new = NULL;
	while (h)
	{
		if (c_word(h->str, " \n\t\v\r") > 1)
			ft_lstadd_back(&new, new_nodes_lexer(h->str, h->token));
		else
			ft_lstadd_back(&new, dup_lexer_node(h));
		h = h->next;
	}
	return (new);
}
