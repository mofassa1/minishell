/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 01:39:12 by mezzine           #+#    #+#             */
/*   Updated: 2024/03/29 05:34:50 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_values(char **env)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	env_init(env);
}

void	safi_rah_salina(int exit_value)
{
	ft_malloc(0, 'f');
	env_clear();
	exit(exit_value);
}

int	*cd_dp(void)
{
	static int	i;

	return (&i);
}

int	*ctrl_c(void)
{
	static int	i;

	return (&i);
}

unsigned int	*get_exit_stat(void)
{
	static unsigned int	exit;

	return (&exit);
}
