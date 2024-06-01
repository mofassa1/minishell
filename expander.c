/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:46:01 by mezzine           #+#    #+#             */
/*   Updated: 2024/04/02 03:40:23 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollar_check(char *s)
{
	while (*s)
	{
		if (*s == '$')
			return (1);
		s++;
	}
	return (0);
}

int	is_heredoc_del(t_lexer *node)
{
	if (!node->prev)
		return (0);
	if (node->prev->token == LESSLESS)
		return (1);
	return (0);
}

int	skip_parenthese(t_lexer **h)
{
	t_lexer	*node;

	node = *h;
	if (node->token == LEFTP && !is_it_btw_parenthes(node))
	{
		while (node && !(node->token == RIGHTP && !is_it_btw_parenthes(node)))
			node = node->next;
	}
	*h = node;
	if (*h == NULL)
		return (1);
	return (0);
}

void	expander(t_lexer *to_parse)
{
	if (!to_parse)
		return ;
	while (to_parse)
	{
		if (skip_parenthese(&to_parse))
			break ;
		if (dollar_check(to_parse->str) && !is_heredoc_del(to_parse))
			to_parse->str = expande(to_parse->str, 0);
		to_parse = to_parse->next;
	}
}
