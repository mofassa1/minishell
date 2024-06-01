/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:17:03 by mezzine           #+#    #+#             */
/*   Updated: 2024/04/02 04:02:26 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size(char *s)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '$' && !check_quoting(s, i)
			&& (s[i + 1] == '\'' || s[i + 1] == '"'))
			size++;
		i++;
	}
	return (size);
}

void	remove_usless_dollars(t_lexer *to_parse)
{
	while (to_parse)
	{
		if (dollar_check(to_parse->str))
			to_parse->str = remove_dollars(to_parse->str);
		to_parse = to_parse->next;
	}
}

int	ambiguous_check(t_lexer *h)
{
	while (h)
	{
		if ((h->token == LESS || h->token == GREAT
				|| h->token == GREATGREAT) && (ft_strlen(h->next->str) == 0
				|| espaces_check(h->next->str) || star_check(h->next)))
		{
			ft_putstr_fd("mini: ", 2);
			ft_putstr_fd(h->next->ori5inal, 2);
			ft_putstr_fd(": ambiguous redirect\n", 2);
			return (1);
		}
		h = h->next;
	}
	return (0);
}

void	ambiguous(t_lexer	**to_parse)
{
	t_lexer	*tmp;

	tmp = *to_parse;
	if (ambiguous_check(*to_parse))
	{
		*get_exit_stat() = 1;
		*to_parse = NULL;
		return ;
	}
}
