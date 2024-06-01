/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:34:42 by mezzine           #+#    #+#             */
/*   Updated: 2024/03/21 02:32:31 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while ((s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	is_rediretion(t_lexer *l)
{
	if (!l)
		return (0);
	if (l->token == LESS || l->token == LESSLESS || l->token == GREAT
		|| l->token == GREATGREAT)
		return (1);
	return (0);
}

void	redirection_here(t_parser *cmd, t_lexer *node)
{
	if (node->token == GREAT)
		ft_lstadd_back_strings(&cmd->outfile, ft_lstnew_strings(node->next->str,
				GREAT));
	else if (node->token == GREATGREAT)
		ft_lstadd_back_strings(&cmd->outfile, ft_lstnew_strings(node->next->str,
				GREATGREAT));
	else if (node->token == LESS)
		ft_lstadd_back_strings(&cmd->infile, ft_lstnew_strings(node->next->str,
				LESS));
	else if (node->token == LESSLESS)
		ft_lstadd_back_strings(&cmd->infile, ft_lstnew_strings(node->next->str,
				LESSLESS));
}

int	nbr_of_quote(char *s)
{
	size_t	i;
	size_t	j;
	size_t	size;

	if (!s)
		return (0);
	i = 0;
	size = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			j = i + 1;
			size++;
			while (s[j] != s[i])
				j++;
			i = j;
		}
		i++;
	}
	return (size);
}
