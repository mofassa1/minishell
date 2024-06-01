/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:39:58 by mezzine           #+#    #+#             */
/*   Updated: 2024/03/21 05:38:35 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	new_lenght1(char *s)
{
	size_t	i;
	size_t	size;

	size = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] == '|' || s[i] == '>' || s[i] == '<')
			&& !check_quoting(s, i))
		{
			size += 2;
			if (s[i + 1] == s[i])
				i++;
		}
		i++;
	}
	return (ft_strlen(s) + size);
}

size_t	new_lenght2(char *s)
{
	size_t	i;
	size_t	size;

	size = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] == ')' || s[i] == '('
				|| (s[i] == '&' && s[i + 1] == '&')) && !check_quoting(s, i))
		{
			if (s[i] == '&')
				size++;
			size += 2;
		}
		i++;
	}
	return (ft_strlen(s) + size);
}

int	nbr_of_quoting_before(char *str, int a, char q)
{
	int	c;

	c = 0;
	a--;
	while (a >= 0)
	{
		if (str[a] == q && !check_quoting(str, a))
			c++;
		a--;
	}
	return (c % 2);
}

int	check_quoting(char *str, int a)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			j = i + 1;
			while (str[j] && str[j] != str[i])
				j++;
			if (a > i && a < j)
				return (1);
			i = j + 1;
		}
		else
			i++;
	}
	return (0);
}
