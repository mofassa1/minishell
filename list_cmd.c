/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:26:04 by mezzine           #+#    #+#             */
/*   Updated: 2024/04/01 04:45:51 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_lstnew_cmd(t_parser *parsed)
{
	t_cmd	*n;

	n = ft_malloc(sizeof(t_cmd), 'm');
	n->cmd = parsed->cmd;
	n->path = cmd_path(ft_strtrim(parsed->cmd));
	n->flags = sts(parsed->flags, parsed->cmd);
	n->infiles = parsed->infile;
	n->outfiles = parsed->outfile;
	if (pipe(n->outfile) == -1)
	{
		perror("pipe");
		exit(1);
	}
	n->next = NULL;
	n->prev = NULL;
	return (n);
}

t_cmd	*ft_lstlast_cmd(t_cmd *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	if (lst)
	{
		if (!*lst)
		{
			*lst = new;
			return ;
		}
		last = ft_lstlast_cmd(*lst);
		last->next = new;
		new->prev = last;
	}
}
