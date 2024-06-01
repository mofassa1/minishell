/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 02:27:08 by mezzine           #+#    #+#             */
/*   Updated: 2024/03/29 05:42:03 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_num(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_exit(char **flags)
{
	if (!flags[1])
		safi_rah_salina(*get_exit_stat());
	if (is_num(flags[1]))
	{
		if (!flags[2])
			safi_rah_salina((unsigned char)ft_atoi(flags[1]));
		else
		{
			ft_putstr_fd("exit\nmini: exit: too many arguments\n", 2);
			return (1);
		}
	}
	else
	{
		ft_putstr_fd("exit\nbash: exit: ", 2);
		ft_putstr_fd(flags[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		safi_rah_salina(255);
	}
	return (0);
}
