/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_opener.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:03:49 by mezzine           #+#    #+#             */
/*   Updated: 2024/03/26 00:58:12 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_write(int fd, char *s, int ex)
{
	char	*str;

	if (ex != 0)
		write(fd, s, ft_strlen(s));
	else
	{
		str = expande(s, 1);
		write(fd, str, ft_strlen(str));
	}
	write(fd, "\n", 1);
}

void	here_doc(char *delimiter, int fd)
{
	char	*s;
	char	*del;
	int		ex;

	del = ft_strtrim(delimiter);
	ex = nbr_of_quote(delimiter);
	while (1)
	{
		s = readline("> ");
		if (!s || !ft_strcmp(del, s))
			break ;
		ft_write(fd, s, ex);
		free(s);
	}
	if (s)
		free(s);
	close(fd);
}

void	open_here_doc(t_cmd *cmd)
{
	t_strings	*infile;

	while (cmd)
	{
		infile = cmd->infiles;
		while (infile)
		{
			if (infile->type == LESSLESS)
				here_doc(infile->str, infile->here_fd);
			infile = infile->next;
		}
		cmd = cmd->next;
	}
}

void	open_all_infiles(t_strings *infile)
{
	while (infile)
	{
		if (infile->type == LESS)
		{
			infile->fd = open(infile->str, O_RDONLY);
			if (infile->fd == -1)
			{
				perror(infile->str);
				exit (1);
			}
		}
		infile = infile->next;
	}
}

void	open_all_outfiles(t_strings *outfile)
{
	while (outfile)
	{
		if (outfile->type == GREAT)
		{
			outfile->fd = open(outfile->str, O_TRUNC | \
					O_WRONLY | O_CREAT, 0644);
			if (outfile->fd == -1)
			{
				perror(outfile->str);
				exit (1);
			}
		}
		else if (outfile->type == GREATGREAT)
		{
			outfile->fd = open(outfile->str, O_APPEND | \
					O_WRONLY | O_CREAT, 0644);
			if (outfile->fd == -1)
			{
				perror(outfile->str);
				exit (1);
			}
		}
		outfile = outfile->next;
	}
}
