/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 05:31:27 by afadouac          #+#    #+#             */
/*   Updated: 2024/04/01 18:23:01 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**get_env_list(void)
{
	static t_env	*g_env_list;

	return (&g_env_list);
}

void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		env++;
	}
}

t_env	*ft_env_new(char *variable, char *content)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->variable = variable;
	if (!ft_strcmp(variable, "SHLVL"))
	{
		new->content = ft_itoa(ft_atoi(content) + 1);
		new->next = NULL;
		free(content);
		return (new);
	}
	new->content = content;
	new->next = NULL;
	return (new);
}

void	env_init_null(void)
{
	t_env	*new;

	new = ft_env_new(ft_strdup_original("PWD"), getcwd(NULL, 0));
	env_lstadd_back(&*get_env_list(), new);
	new = ft_env_new(ft_strdup_original("SHLVL"), ft_strdup_original("0"));
	env_lstadd_back(&*get_env_list(), new);
	new = ft_env_new(ft_strdup_original("_"),
			ft_strdup_original("/usr/bin/env"));
	env_lstadd_back(&*get_env_list(), new);
}
