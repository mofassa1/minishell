/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:45:02 by afadouac          #+#    #+#             */
/*   Updated: 2024/03/26 00:58:04 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_couter(t_strings *infile)
{
	int	c;

	c = 0;
	while (infile)
	{
		if (infile->type == LESSLESS)
			c++;
		infile = infile->next;
	}
	return (c);
}

void	check_here_doc_limite(t_cmd *cmds)
{
	int	c;

	c = 0;
	while (cmds)
	{
		c += here_couter(cmds->infiles);
		if (c > 16)
		{
			ft_putstr_fd("mini: maximum here-document count exceeded\n", 2);
			exit(2);
		}
		cmds = cmds->next;
	}
}

void	fill_here_fd(t_cmd *cmd)
{
	int			end[2];
	t_strings	*infile;

	while (cmd)
	{
		infile = cmd->infiles;
		while (infile)
		{
			if (infile->type == LESSLESS)
			{
				if (pipe(end) == -1)
					exit(1);
				infile->fd = end[0];
				infile->here_fd = end[1];
			}
			infile = infile->next;
		}
		cmd = cmd->next;
	}
}

void	close_here_fd(t_cmd *cmd)
{
	t_strings	*infile;

	while (cmd)
	{
		infile = cmd->infiles;
		while (infile)
		{
			if (infile->type == LESSLESS)
				close(infile->here_fd);
			infile = infile->next;
		}
		cmd = cmd->next;
	}
}

int	here_doc_opener(t_cmd *cmd)
{
	pid_t		i;
	int			s;
	t_cmd		*tmp;

	fill_here_fd(cmd);
	tmp = cmd;
	i = fork();
	if (i == 0)
	{
		signal(SIGINT, SIG_DFL);
		open_here_doc(cmd);
		exit (0);
	}
	close_here_fd(tmp);
	wait(&s);
	return (s);
}
