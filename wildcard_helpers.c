/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 04:32:06 by afadouac          #+#    #+#             */
/*   Updated: 2024/04/01 03:37:27 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_nodes_in(t_lexer *new_nodes, t_lexer **h, t_lexer *prev, t_lexer *next)
{
	if (new_nodes)
	{
		if (!prev)
		{
			*h = new_nodes;
			ft_lstadd_back(&new_nodes, next);
		}
		else
		{
			prev->next = NULL;
			ft_lstadd_back(&prev, new_nodes);
			ft_lstadd_back(&new_nodes, next);
		}
		return (1);
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!needle[i])
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		if (haystack[i] == needle[j])
		{
			while (haystack[i + j] == needle[j] && i + j < len)
			{
				if (needle[j + 1] == '\0')
					return ((char *)haystack + i);
				j++;
			}
		}
		i++;
		j = 0;
	}
	return (NULL);
}

t_lexer	*ft_lst_last(t_lexer **lst)
{
	t_lexer	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (!tmp->next)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

void	sort_lex(t_lexer **lex)
{
	t_lexer	*tmp;
	char	*str;

	tmp = *lex;
	while (tmp)
	{
		if (tmp->next && ft_strcmp(tmp->str, tmp->next->str) >= 0)
		{
			str = tmp->str;
			tmp->str = tmp->next->str;
			tmp->next->str = str;
			tmp = *lex;
		}
		else
			tmp = tmp->next;
	}
}

int	are_all_stars(char *str)
{
	int		i;

	i = 0;
	while (str[i] == '*')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}
