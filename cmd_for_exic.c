/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_for_exic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:48:42 by afadouac          #+#    #+#             */
/*   Updated: 2024/04/02 03:46:20 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_remover_strings(t_strings *s)
{
	while (s)
	{
		if (s->type != LESSLESS)
			s->str = ft_strtrim(s->str);
		s = s->next;
	}
}

void	quote_remover(t_parser *parsed)
{
	while (parsed)
	{
		quote_remover_strings(parsed->flags);
		quote_remover_strings(parsed->infile);
		quote_remover_strings(parsed->outfile);
		parsed = parsed->next;
	}
}

t_cmd	*create_cmds(t_parser *parsed)
{
	t_cmd	*cmds;

	cmds = NULL;
	while (parsed)
	{
		ft_lstadd_back_cmd(&cmds, ft_lstnew_cmd(parsed));
		parsed = parsed->next;
	}
	return (cmds);
}
