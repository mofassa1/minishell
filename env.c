/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 21:20:52 by afadouac          #+#    #+#             */
/*   Updated: 2024/04/01 18:16:13 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*return_last_str(char **v)
{
	int	i;

	i = 0;
	while (v[i + 1])
		i++;
	return (v[i]);
}

void	set__value(t_cmd *cmds)
{
	char	*s;

	if (!cmds->flags[0] || cmds->next)
		set_env_content(get_env("_"), NULL);
	else
	{
		s = return_last_str(cmds->flags);
		if (s[0] == '(' && s[ft_strlen(s) - 1] == ')')
			return ;
		set_env_content(get_env("_"), ft_strdup_original(s));
	}
}

char	**env_to_str(void)
{
	char	**str;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = *get_env_list();
	str = ft_malloc((env_lstsize(tmp) + 1) * sizeof(char **), 'm');
	while (tmp)
	{
		if (!ft_strcmp(tmp->variable, "_"))
		{
			str[i] = ft_strjoin(ft_strjoin(tmp->variable, "="), "/usr/bin/env");
			i++;
		}
		else if (tmp->content)
		{
			str[i] = ft_strjoin(ft_strjoin(tmp->variable, "="), tmp->content);
			i++;
		}
		tmp = tmp->next;
	}
	str[i] = NULL;
	return (str);
}

void	env_init(char **env)
{
	int		i;
	char	*var;
	char	*con;

	i = 0;
	*get_env_list() = NULL;
	if (!env[0])
		env_init_null();
	while (env[i])
	{
		var = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		con = ft_strdup_original(getenv(var));
		env_lstadd_back(&*get_env_list(), ft_env_new(var, con));
		i++;
	}
	set_pwdpath(get_env_content("PWD"));
}
