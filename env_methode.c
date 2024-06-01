/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_methode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:43:24 by mezzine           #+#    #+#             */
/*   Updated: 2024/04/01 18:16:13 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_pwdpath(void)
{
	static char	*path;

	return (&path);
}

void	set_pwdpath(char *str)
{
	if (*get_pwdpath())
		free(*get_pwdpath());
	*get_pwdpath() = ft_strdup_original(str);
}

t_env	*get_env(char *var)
{
	t_env	*tmp;

	tmp = *get_env_list();
	while (tmp)
	{
		if (!ft_strcmp(tmp->variable, var))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	set_env_content(t_env *env, char *s)
{
	if (!env)
	{
		if (s)
			free(s);
		return (-1);
	}
	if (env->content)
		free(env->content);
	env->content = s;
	return (0);
}

char	*get_env_content(char *var)
{
	if (get_env(var))
		return (get_env(var)->content);
	return (NULL);
}
