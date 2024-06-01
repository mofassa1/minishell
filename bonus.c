/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:12:52 by mezzine           #+#    #+#             */
/*   Updated: 2024/04/02 03:38:35 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_it_btw_parenthes(t_lexer *h)
{
	t_lexer	*tmp;
	int		c;

	c = 0;
	if (!h)
		return (0);
	tmp = h->prev;
	while (tmp)
	{
		if (tmp->token == LEFTP && c == 0)
			return (1);
		else if (tmp->token == RIGHTP)
			c++;
		else if (tmp->token == LEFTP)
			c--;
		tmp = tmp->prev;
	}
	return (0);
}

int	truth_value(t_lexer *to_parse)
{
	t_lexer	*new_h;
	t_lexer	*h;
	int		true_table;

	h = to_parse;
	while (to_parse->next)
	{
		if ((to_parse->next->token == OR || to_parse->next->token == AND)
			&& !is_it_btw_parenthes(to_parse->next))
			break ;
		to_parse = to_parse->next;
	}
	new_h = lexer_copy(h, to_parse->next);
	true_table = traitement(new_h);
	return (true_table);
}

int	logic_gate(char *new)
{
	int		true_table;
	t_lexer	*to_parse;

	to_parse = lexer(new);
	if (!to_parse)
		return (1);
	true_table = truth_value(to_parse);
	while (to_parse)
	{
		if (to_parse->token == OR && !is_it_btw_parenthes(to_parse))
			true_table = true_table || truth_value(to_parse->next);
		else if (to_parse->token == AND && !is_it_btw_parenthes(to_parse))
			true_table = true_table && truth_value(to_parse->next);
		to_parse = to_parse->next;
	}
	return (*get_exit_stat());
}
