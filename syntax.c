/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 21:49:03 by mezzine           #+#    #+#             */
/*   Updated: 2024/04/01 21:45:28 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_p_a_o(t_lexer *node)
{
	if (node->token == AND || node->token == OR || node->token == PIPE)
	{
		if (node->next == NULL || node->next->token == PIPE
			|| node->next->token == AND || node->next->token == OR)
			return (1);
	}
	return (0);
}

int	syntax_of_w(t_lexer **h)
{
	t_lexer	*node;

	node = *h;
	if (node->token == WORD && node->next)
	{
		if (node->next->token == LEFTP)
		{
			if (!node->prev || node->prev->token != WORD)
				*h = node->next;
			return (1);
		}
	}
	return (0);
}

int	syntax_of_redirection(t_lexer *node)
{
	if (node->token == LESS || node->token == LESSLESS || node->token == GREAT
		|| node->token == GREATGREAT)
	{
		if (node->next == NULL || node->next->token != WORD)
			return (1);
	}
	return (0);
}

int	syntax_p(t_lexer *node)
{
	if (node->token == LEFTP && node->next != NULL)
	{
		if (node->next->token == RIGHTP || node->next->token == PIPE)
			return (1);
	}
	if (node->token == RIGHTP && node->next != NULL)
	{
		if (node->next->token == LEFTP || node->next->token == WORD)
			return (1);
	}
	return (0);
}
