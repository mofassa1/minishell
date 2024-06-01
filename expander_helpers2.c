/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 02:48:25 by mezzine           #+#    #+#             */
/*   Updated: 2024/03/21 02:29:15 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_expandeable(char *s, int a, int fex)
{
	if (fex == 1)
		return (1);
	if (check_quoting(s, a))
	{
		if (!nbr_of_quoting_before(s, a, '\''))
			return (1);
		return (0);
	}
	return (1);
}

void	copy(char *new, char *s, int *j)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		new[*j] = s[i];
		(*j)++;
		i++;
	}
}

int	allowed_char(char c)
{
	if ((c <= '9' && c >= '0') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

char	*variable_name_geter(char *s)
{
	int		i;
	char	*new;
	char	c;

	i = 0;
	while (allowed_char(s[i]))
		i++;
	c = s[i];
	s[i] = '\0';
	new = ft_strdup(s);
	s[i] = c;
	return (new);
}
