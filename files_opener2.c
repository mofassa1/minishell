/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_opener2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:52:16 by afadouac          #+#    #+#             */
/*   Updated: 2024/03/28 01:11:16 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dish_files_closer(t_strings *file)
{
	while (file->next)
	{
		close(file->fd);
		file = file->next;
	}
}

void	infile_o(t_cmd	*cmd)
{
	t_strings	*infile;

	infile = cmd->infiles;
	if (!infile)
	{
		cmd->infile = 0;
		return ;
	}
	if (!ft_strcmp(infile->str, "pipe"))
	{
		cmd->infile = cmd->prev->outfile[0];
		return ;
	}
	open_all_infiles(infile);
	cmd->infile = ft_lstlast_strings(infile)->fd;
	dish_files_closer(infile);
}

void	outfile_o(t_cmd *cmd)
{
	t_strings	*outfile;

	outfile = cmd->outfiles;
	if (!outfile)
	{
		close(cmd->outfile[1]);
		cmd->outfile[1] = 1;
		return ;
	}
	if (!ft_strcmp(outfile->str, "pipe"))
		return ;
	close(cmd->outfile[1]);
	open_all_outfiles(outfile);
	cmd->outfile[1] = ft_lstlast_strings(outfile)->fd;
	dish_files_closer(outfile);
}
