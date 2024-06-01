/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 00:41:24 by afadouac          #+#    #+#             */
/*   Updated: 2024/04/01 21:23:44 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_the_rest_is_n(char *s)
{
	if (!*s)
		return (0);
	while (*s)
	{
		if (*s != 'n')
			return (0);
		s++;
	}
	return (1);
}

void	ft_echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->flags[i] && cmd->flags[i][0] == '-'
		&& is_the_rest_is_n(cmd->flags[i] + 1))
		i++;
	while (cmd->flags[i])
	{
		printf("%s", cmd->flags[i]);
		if (cmd->flags[i + 1])
			printf(" ");
		i++;
	}
	if (!(cmd->flags[1] && cmd->flags[1][0] == '-'
		&& is_the_rest_is_n(cmd->flags[1] + 1)))
		printf("\n");
}
