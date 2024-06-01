/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:20:09 by mezzine           #+#    #+#             */
/*   Updated: 2024/04/02 04:53:49 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_executor(t_cmd *cmd, char **env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	infile_o(cmd);
	outfile_o(cmd);
	if (!cmd->cmd)
		safi_rah_salina(0);
	dup2(cmd->infile, 0);
	dup2(cmd->outfile[1], 1);
	close_files(cmd);
	if (cmd->cmd[0] == '(' && cmd->cmd[ft_strlen(cmd->cmd) - 1] == ')')
	{
		cmd->cmd = cmd->cmd + 1;
		cmd->cmd[ft_strlen(cmd->cmd) - 1] = '\0';
		safi_rah_salina (logic_gate(cmd->cmd));
	}
	cmd->cmd = ft_strtrim(cmd->cmd);
	if (check_builtin(cmd->cmd))
		safi_rah_salina(builtin_cmds(cmd, env));
	execve(cmd->path, cmd->flags, env);
	error_of_exit(cmd->cmd);
}

void	wait_proccess(t_cmd *cmd)
{
	int	status;

	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		cmd = cmd->next;
	}
	if (WIFEXITED(status))
		*get_exit_stat() = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*get_exit_stat() = 128 + WTERMSIG(status);
}

void	execute(t_cmd *cmds)
{
	t_cmd	*tmp;
	char	**env;

	env = env_to_str();
	tmp = cmds;
	if (here_doc_opener(cmds) != 0)
	{
		*get_exit_stat() = 1;
		return ;
	}
	set__value(cmds);
	while (cmds)
	{
		cmds->pid = fork();
		if (cmds->pid == 0)
			cmd_executor(cmds, env);
		cmds = cmds->next;
	}
	close_files(tmp);
	wait_proccess(tmp);
}

int	executer(t_parser *parsed)
{
	t_cmd	*cmds;
	char	*cmd;

	if (!parsed)
		return (!(*get_exit_stat()));
	quote_remover(parsed);
	cmds = create_cmds(parsed);
	check_here_doc_limite(cmds);
	cmd = ft_strtrim(cmds->cmd);
	if ((!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "export")
			|| !ft_strcmp(cmd, "unset")
			|| !ft_strcmp(cmd, "exit")) && !cmds->next)
	{
		run_in_parent(cmds);
		return (!(*get_exit_stat()));
	}
	execute(cmds);
	return (!(*get_exit_stat()));
}
