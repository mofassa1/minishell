/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 05:25:16 by afadouac          #+#    #+#             */
/*   Updated: 2024/04/01 18:16:13 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_int_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	ft_export_only(void)
{
	char	**str;
	char	*tmp;
	int		i;

	i = 0;
	str = fill_array();
	str = sort_str(str);
	while (str[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(str[i], 1);
		tmp = get_env_content(str[i]);
		if (tmp)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tmp, 1);
			ft_putstr_fd("\"\n", 1);
		}
		else
			ft_putstr_fd("\n", 1);
		i++;
	}
	return (0);
}

int	all_good(char *s)
{
	int	i;

	i = 0;
	if (ft_isdigit(s[i]) || s[i] == '='
		|| (s[i] == '+' && s[i + 1] == '='))
		return (0);
	while (s[i] && s[i] != '='
		&& !(s[i] == '+' && s[i + 1] == '='))
	{
		if (!allowed_char(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	put_var(char *s)
{
	char	*content;
	char	*var_name;
	char	c;

	c = 'n';
	content = NULL;
	if (ft_strchr(s, '='))
		content = ft_strchr(s, '=') + 1;
	if (ft_strchr(s, '+') && s[ft_int_strchr(s, '+') + 1] == '=')
	{
		*ft_strchr(s, '+') = '\0';
		c = 'j';
	}
	else if (ft_strchr(s, '='))
		*ft_strchr(s, '=') = '\0';
	var_name = s;
	if (get_env(var_name))
	{
		if (c == 'j')
			content = ft_strjoin(get_env_content(var_name), content);
		set_env_content(get_env(var_name), ft_strdup_original(content));
		return ;
	}
	env_lstadd_back(&*get_env_list(), ft_lstnew_env(var_name, content));
}

int	ft_export(t_cmd *cmd)
{
	int	i;
	int	s;

	i = 1;
	s = 0;
	while (cmd->flags[i])
	{
		if (all_good(cmd->flags[i]))
		{
			if (!get_env(cmd->flags[i]))
				put_var(cmd->flags[i]);
		}
		else
		{
			ft_putstr_fd("mini : export: `", 2);
			ft_putstr_fd(cmd->flags[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			s = 1;
		}
		i++;
	}
	return (s);
}
