/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:21:40 by mezzine           #+#    #+#             */
/*   Updated: 2024/04/01 05:21:42 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_printer(t_lexer *tmp)
{
	if (tmp == NULL)
		ft_putstr_fd("mini: syntax error near unexpected token `newline'\n", 2);
	else
	{
		ft_putstr_fd("mini: syntax error near unexpected token `", 2);
		ft_putstr_fd(tmp->str, 2);
		ft_putstr_fd("'\n", 2);
	}
	*get_exit_stat() = 258;
	return (-1);
}

void	close_files(t_cmd *cmds)
{
	t_cmd	*prev;

	prev = cmds->prev;
	while (prev)
	{
		ft_close(prev->outfile[0]);
		ft_close(prev->outfile[1]);
		ft_close(prev->infile);
		prev = prev->prev;
	}
	while (cmds)
	{
		ft_close(cmds->outfile[0]);
		ft_close(cmds->outfile[1]);
		ft_close(cmds->infile);
		cmds = cmds->next;
	}
}

int	is_directory(char	*path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == -1)
	{
		perror("stat");
		return (0);
	}
	return (S_ISDIR(statbuf.st_mode));
}

void	print_error(char *path)
{
	ft_putstr_fd("mini: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": is a directory\n", 2);
}

void	error_of_exit(char *cmd)
{
	if (ft_strchr(cmd, '/') || !get_env("PATH"))
	{
		if (!access(cmd, F_OK))
		{
			if (is_directory(cmd))
				print_error(cmd);
			else if (access(cmd, X_OK))
			{
				ft_putstr_fd("mini: ", 2);
				perror(cmd);
			}
			safi_rah_salina(126);
		}
		else
		{
			ft_putstr_fd("mini: ", 2);
			perror(cmd);
			safi_rah_salina(127);
		}
	}
	error_p(cmd);
	safi_rah_salina(127);
}
