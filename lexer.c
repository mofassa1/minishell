/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:52:31 by mezzine           #+#    #+#             */
/*   Updated: 2024/03/22 21:56:34 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	quote_counter(char *s, char ch)
{
	size_t	i;
	size_t	c;

	i = 0;
	c = 0;
	while (s[i])
	{
		if (s[i] == ch && !check_quoting(s, i))
			c++;
		i++;
	}
	return (c);
}

int	quote_checker(char *s)
{
	size_t	i;

	i = 0;
	if (quote_counter(s, '"') % 2)
	{
		write(2, "mini : syntax error unclosed quote(s)\n", 39);
		return (1);
	}
	if (quote_counter(s, '\'') % 2)
	{
		write(2, "mini : syntax error unclosed quote(s)\n", 39);
		return (1);
	}
	if (quote_counter(s, '(') != quote_counter(s, ')'))
	{
		write(2, "mini : syntax error parenthesis error\n", 39);
		return (1);
	}
	return (0);
}

int	check_syntax(t_lexer *h)
{
	t_lexer	*tmp;

	if (!h)
		return (-1);
	tmp = h;
	if (tmp->token == PIPE || tmp->token == OR || tmp->token == AND)
		return (error_printer(tmp));
	while (tmp)
	{
		if (syntax_p_a_o(tmp) || syntax_of_redirection(tmp) || syntax_p(tmp)
			|| syntax_of_w(&tmp))
			return (error_printer(tmp->next));
		tmp = tmp->next;
	}
	return (1);
}

t_lexer	*lexer(char *s)
{
	t_lexer	*h;

	if (!s || !s[0])
		return (NULL);
	if (quote_checker(s))
		return (NULL);
	h = spaces_separator(s);
	if (check_syntax(h) == -1)
		h = NULL;
	remove_usless_dollars(h);
	return (h);
}
