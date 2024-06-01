/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 21:11:07 by mezzine           #+#    #+#             */
/*   Updated: 2024/04/01 23:43:29 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_in_parent(t_cmd *cmds)
{
	int	in;
	int	out;

	in = dup(0);
	out = dup(1);
	set__value(cmds);
	infile_o(cmds);
	outfile_o(cmds);
	dup2(cmds->infile, 0);
	dup2(cmds->outfile[1], 1);
	close_files(cmds);
	cmds->cmd = ft_strtrim(cmds->cmd);
	*get_exit_stat() = builtin_cmds(cmds, NULL);
	dup2(in, 0);
	dup2(out, 1);
}

int	check_builtin(char *s)
{
	if (!ft_strcmp(s, "echo") || !ft_strcmp(s, "pwd")
		|| !ft_strcmp(s, "env") || !ft_strcmp(s, "exit")
		|| !ft_strcmp(s, "cd") || !ft_strcmp(s, "export")
		|| !ft_strcmp(s, "unset"))
		return (1);
	return (0);
}

int	builtin_cmds(t_cmd *cmd, char **env)
{
	if (!ft_strcmp(cmd->cmd, "export") && cmd->flags[1] == NULL)
		return (ft_export_only());
	else if (!ft_strcmp(cmd->cmd, "export"))
		return (ft_export(cmd));
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd->cmd, "cd"))
		return (ft_cd(cmd));
	else if (!ft_strcmp(cmd->cmd, "unset"))
		return (ft_unset(cmd));
	else if (!ft_strcmp(cmd->cmd, "env"))
		ft_env(env);
	else if (!ft_strcmp(cmd->cmd, "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd->cmd, "exit"))
		return (ft_exit(cmd->flags));
	return (0);
}
