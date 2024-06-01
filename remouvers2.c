/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remouvers2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 02:06:48 by afadouac          #+#    #+#             */
/*   Updated: 2024/03/21 02:07:24 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_dollars(char *s)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_malloc((ft_strlen(s) - size(s) + 1) * sizeof(char), 'm');
	i = j;
	while (s[i])
	{
		if (s[i] == '$' && !check_quoting(s, i)
			&& (s[i + 1] == '\'' || s[i + 1] == '"'))
		{
			i++;
			continue ;
		}
		else
			new[j++] = s[i++];
	}
	new[j] = '\0';
	return (new);
}
