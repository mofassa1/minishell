/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:00:12 by afadouac          #+#    #+#             */
/*   Updated: 2024/03/24 22:08:29 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (i < dstsize - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s1)
{
	char	*c;
	size_t	i;

	i = ft_strlen(s1);
	c = ft_malloc(i + 1, 'm');
	if (c == NULL)
		return (c);
	ft_strlcpy(c, s1, i + 1);
	return (c);
}

t_tokens	tokenizer(char *s)
{
	if (!ft_strcmp(">", s))
		return (GREAT);
	else if (!ft_strcmp("<", s))
		return (LESS);
	else if (!ft_strcmp(">>", s))
		return (GREATGREAT);
	else if (!ft_strcmp("<<", s))
		return (LESSLESS);
	else if (!ft_strcmp("||", s))
		return (OR);
	else if (!ft_strcmp("&&", s))
		return (AND);
	else if (!ft_strcmp("|", s))
		return (PIPE);
	else if (!ft_strcmp("(", s))
		return (LEFTP);
	else if (!ft_strcmp(")", s))
		return (RIGHTP);
	else
		return (WORD);
}

t_lexer	*spaces_separator(char *s)
{
	t_lexer	*h;
	char	**l;
	int		i;

	i = 0;
	h = NULL;
	l = ft_split(s, " \n\t\v\r");
	while (l[i])
	{
		ft_lstadd_back(&h, ft_lstnew(l[i], tokenizer(l[i])));
		i++;
	}
	return (h);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
