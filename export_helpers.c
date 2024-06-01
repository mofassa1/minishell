/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 03:30:22 by afadouac          #+#    #+#             */
/*   Updated: 2024/04/01 18:16:13 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**sort_str(char **str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] != NULL)
	{
		if (str[i + 1] != NULL && ft_strcmp(str[i], str[i + 1]) >= 0)
		{
			tmp = str[i];
			str[i] = str[i + 1];
			str[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
	return (str);
}

char	**fill_array(void)
{
	char	**str;
	t_env	*env;
	int		i;

	i = 0;
	env = *get_env_list();
	str = ft_malloc((env_lstsize(*get_env_list()) + 1) * sizeof(char *), 'm');
	while (env)
	{
		if (!ft_strcmp(env->variable, "_"))
		{
			env = env->next;
			continue ;
		}
		str[i] = env->variable;
		i++;
		env = env->next;
	}
	str[i] = NULL;
	return (str);
}
