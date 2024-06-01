/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 17:42:00 by mezzine           #+#    #+#             */
/*   Updated: 2024/03/23 11:43:44 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_sep(char *str, int a, char *charset)
{
	int	i;
	int	c;

	if (!str)
		return (0);
	c = str[a];
	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i] && !check_quoting(str, a))
			return (1);
		i++;
	}
	return (0);
}

int	c_word(char *str, char *charset)
{
	int	i;
	int	w;

	w = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && check_sep(str, i, charset))
			i++;
		if (str[i] != '\0')
			w++;
		while (str[i] != '\0' && !check_sep(str, i, charset))
			i++;
	}
	return (w);
}

int	c_char(char *str, char *charset)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0' && !check_sep(str, i, charset))
	{
		c++;
		i++;
	}
	return (c);
}

char	*word(char *str, char *charset)
{
	char	*w;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	w = (char *)ft_malloc(c_char(str, charset) + 1, 'm');
	while (str[i] != '\0' && !check_sep(str, i, charset))
	{
		w[i] = str[i];
		i++;
	}
	w[i] = '\0';
	return (w);
}

char	**ft_split(char *str, char *charset)
{
	char	**split;
	int		i;
	int		w;

	w = 0;
	i = 0;
	split = (char **)ft_malloc(sizeof(char **) * (c_word(str, charset) + 1),
			'm');
	while (str && str[i] != '\0')
	{
		while (str[i] != '\0' && check_sep(str, i, charset))
			i++;
		if (str[i] != '\0')
		{
			split[w] = word(str + i, charset);
			w++;
		}
		while (str[i] != '\0' && !check_sep(str, i, charset))
			i++;
	}
	split[w] = 0;
	return (split);
}
