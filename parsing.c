/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:57:53 by afadouac          #+#    #+#             */
/*   Updated: 2024/04/01 17:50:50 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_flags(t_parser *cmd, t_lexer *node)
{
	if (ft_strlen(node->str) == 0)
		return ;
	if (cmd->cmd == NULL)
		cmd->cmd = node->str;
	else
		ft_lstadd_back_strings(&cmd->flags, ft_lstnew_strings(node->str, WORD));
}

int	check_pipe_before(t_lexer *node)
{
	if (node)
		node = node->prev;
	while (node)
	{
		if (node->token == AND || node->token == OR)
			break ;
		if (node->token == PIPE)
			return (1);
		node = node->prev;
	}
	return (0);
}

void	parenthes(t_lexer **h, t_parser *cmd)
{
	t_lexer	*node;
	int		c;

	c = 0;
	node = *h;
	if (node->token == LEFTP && !cmd->cmd)
	{
		cmd->cmd = node->str;
		node = node->next;
		while (!(node->token == RIGHTP && c == 0))
		{
			c += c_increase(node->token);
			cmd->cmd = ft_strjoin(cmd->cmd, node->str);
			cmd->cmd = ft_strjoin(cmd->cmd, " ");
			node = node->next;
		}
		cmd->cmd = ft_strjoin(cmd->cmd, node->str);
	}
	*h = node;
}

t_parser	*cmd_creator(t_lexer **to_parse)
{
	t_lexer		*node;
	t_parser	*cmd;

	cmd = ft_lstnew_parser();
	node = *to_parse;
	while (node)
	{
		if (node->token == PIPE)
		{
			if (cmd->outfile == NULL)
				ft_lstadd_back_strings(&cmd->outfile, ft_lstnew_strings("pipe",
						GREAT));
			break ;
		}
		parenthes(&node, cmd);
		if (is_rediretion(node))
			redirection_here(cmd, node);
		else if (node->token == WORD && !is_rediretion(node->prev))
			cmd_flags(cmd, node);
		node = node->next;
	}
	if (cmd->infile == NULL && check_pipe_before(*to_parse))
		ft_lstadd_back_strings(&cmd->infile, ft_lstnew_strings("pipe", GREAT));
	*to_parse = node;
	return (cmd);
}

t_parser	*parser(t_lexer *to_parse)
{
	t_parser	*parsed;

	parsed = NULL;
	while (to_parse)
	{
		ft_lstadd_back_parser(&parsed, cmd_creator(&to_parse));
		if (to_parse)
			to_parse = to_parse->next;
	}
	return (parsed);
}
