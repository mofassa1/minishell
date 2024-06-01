/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:03:15 by afadouac          #+#    #+#             */
/*   Updated: 2024/04/01 03:38:47 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last_chec(int *arr, char *str, char *file)
{
	if (str[0] != '*' && arr[0] != 0)
		return (0);
	if (str[ft_strlen(str) - 1] != '*')
		if (!ft_strrcmp(str, file, ft_strlen(str), ft_strlen(file)))
			return (0);
	return (1);
}

int	is_wildcard(char *file, char *str)
{
	char	**s;
	int		*tmp;
	int		i;

	i = 0;
	s = ft_split(str, "*");
	tmp = (int *)ft_malloc(strings_count(s) * sizeof(int), 'm');
	while (s[i])
	{
		if (!ft_strnstr(file, s[i], ft_strlen(file)))
			return (0);
		tmp[i] = (ft_strnstr(file, s[i], ft_strlen(file)) - file);
		if (is_doubled(tmp, i) || !sorted(tmp, i))
		{
			if (!ft_strnstr(file + tmp[i] + 1, s[i], ft_strlen(file)))
				return (0);
			tmp[i] = (ft_strnstr(file + tmp[i] + 1, \
					s[i], ft_strlen(file)) - file);
		}
		i++;
	}
	if (!sorted(tmp, i - 1))
		return (0);
	return (last_chec(tmp, str, file));
}

void	ori5inal_adder(t_lexer *lex, char *str)
{
	if (!lex)
		return ;
	while (lex)
	{
		lex->ori5inal = ft_strdup(str);
		lex = lex->next;
	}
}

t_lexer	*fill_wildcard(char *str)
{
	struct dirent	*file;
	t_lexer			*lex;
	t_lexer			*tmp;
	DIR				*dir;

	lex = NULL;
	dir = opendir(".");
	file = readdir(dir);
	while (file != NULL)
	{
		if (are_all_stars(str))
		{
			if (file->d_name[0] != '.')
				ft_lstadd_back(&lex, ft_lstnew(ft_strdup(file->d_name), WORD));
		}
		else if (is_wildcard(file->d_name, str))
		{
			tmp = ft_lstnew(ft_strdup(file->d_name), WORD);
			ft_lstadd_back(&lex, tmp);
		}
		file = readdir(dir);
	}
	closedir(dir);
	ori5inal_adder(lex, str);
	return (lex);
}

t_lexer	*wildcard(t_lexer *h)
{
	t_lexer	*new_nodes;
	t_lexer	*next;
	t_lexer	*tmp;

	tmp = h;
	while (tmp)
	{
		if (ft_strchr(tmp->str, '*'))
		{
			new_nodes = fill_wildcard(tmp->str);
			sort_lex(&new_nodes);
			next = tmp->next;
			if (add_nodes_in(new_nodes, &h, tmp->prev, next))
			{
				tmp = next;
				continue ;
			}
		}
		tmp = tmp->next;
	}
	return (h);
}
