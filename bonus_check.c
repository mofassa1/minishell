/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:06:12 by mezzine           #+#    #+#             */
/*   Updated: 2024/03/21 22:33:13 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	c_increase(t_tokens t)
{
	if (t == RIGHTP)
		return (1);
	else if (t == LEFTP)
		return (-1);
	return (0);
}

int	star_check(t_lexer *h)
{
	int		c;
	char	*str;

	c = 1;
	if (ft_strchr(h->ori5inal, '*')
		&& !check_quoting(h->ori5inal, ft_int_strchr(h->ori5inal, '*')))
	{
		str = h->ori5inal;
		h = h->next;
		while (h)
		{
			if (!ft_strcmp(str, h->ori5inal))
				c++;
			else
				break ;
			h = h->next;
		}
	}
	if (c > 1)
		return (1);
	return (0);
}

int	espaces_check(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if ((str[i] == ' ' || str[i] == '\n' \
			|| str[i] == '\t') && !check_quoting(str, i))
			return (1);
		i++;
	}
	return (0);
}
