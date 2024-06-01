/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 02:02:55 by afadouac          #+#    #+#             */
/*   Updated: 2024/04/02 23:22:40 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	**get_pid_head(void)
{
	static t_cmd	*h;

	return (&h);
}

void	kill_childs(void)
{
	t_cmd	*h;

	h = *get_pid_head();
	while (h)
	{
		kill(h->pid, SIGKILL);
		h = h->next;
	}
}

void	error_p(char *s)
{
	ft_putstr_fd("mini: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	ft_close(int fd)
{
	if (fd != 0 && fd != 1)
		close(fd);
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	if (*ctrl_c() == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	*get_exit_stat() = 1;
	*ctrl_c() = 0;
}
