/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:04:01 by afadouac          #+#    #+#             */
/*   Updated: 2024/04/01 18:17:48 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_cmd(t_env **new)
{
	t_env	*tmp;

	tmp = *new;
	free((tmp->content));
	free((tmp->variable));
	free(tmp);
}

int	check_unset_error(char *arg)
{
	int	i;

	i = 0;
	if (!ft_strcmp(arg, "PWD") && get_env("PWD"))
		set_pwdpath(NULL);
	if (arg[0] == '_' && arg[1] == '\0')
		return (0);
	while (arg[i])
	{
		if (!allowed_char(arg[i]) || ft_isdigit(arg[0]))
		{
			ft_putstr_fd("mini : unset: `", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

t_env	*get_prev(char *var)
{
	t_env	*tmp;

	tmp = *get_env_list();
	while (tmp->next)
	{
		if (!ft_strcmp(tmp->next->variable, var))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	relinek_list(t_env **courent, t_env **prev)
{
	t_env	*tmp;
	t_env	*previous;

	tmp = *courent;
	previous = *prev;
	if (!previous)
	{
		tmp = *get_env_list();
		*get_env_list() = (*get_env_list())->next;
	}
	else
		previous->next = tmp->next;
}

int	ft_unset(t_cmd *cmd)
{
	t_env	*tmp;
	t_env	*prev;
	int		i;
	int		s;

	i = 0;
	s = 0;
	while (cmd->flags[++i])
	{
		if (!ft_strcmp(cmd->flags[i], "_"))
			continue ;
		if (check_unset_error(cmd->flags[i]))
		{
			if (get_env(cmd->flags[i]))
			{
				tmp = get_env(cmd->flags[i]);
				prev = get_prev(cmd->flags[i]);
				relinek_list(&tmp, &prev);
				ft_clear_cmd(&tmp);
			}
		}
		else
			s = 1;
	}
	return (s);
}
