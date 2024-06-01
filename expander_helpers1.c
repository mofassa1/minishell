/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 02:46:28 by mezzine           #+#    #+#             */
/*   Updated: 2024/03/26 02:01:29 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_check(char c)
{
	if (allowed_char(c) || c == '?')
		return (1);
	return (0);
}

int	var_case_size(char c, int *size, int *i)
{
	char	*s;

	if (ft_isdigit(c) || c == '?')
	{
		s = ft_itoa(*get_exit_stat());
		if (c == '?')
			*size += ft_strlen(s);
		if (ft_isdigit(c) || c == '?')
			(*i)++;
		free(s);
		return (1);
	}
	return (0);
}

int	expande_size(char *s, int fex)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (s[i])
	{
		if (s[i] == '$' && first_check(s[i + 1]) && is_expandeable(s, i, fex))
		{
			if (var_case_size(s[++i], &size, &i))
				continue ;
			size += ft_strlen(get_env_content(variable_name_geter(s + i)));
			while (allowed_char(s[i]))
				i++;
		}
		else
		{
			i++;
			size++;
		}
	}
	return (size);
}

int	var_case(char c, char *new, int *j, int *i)
{
	char	*s;

	if (ft_isdigit(c) || c == '?')
	{
		s = ft_itoa(*get_exit_stat());
		if (c == '?')
			copy(new, s, j);
		if (ft_isdigit(c) || c == '?')
			(*i)++;
		free(s);
		return (1);
	}
	return (0);
}

char	*expande(char *s, int fex)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_malloc(expande_size(s, fex) + 1, 'm');
	while (s[i])
	{
		if (s[i] == '$' && first_check(s[i + 1]) && is_expandeable(s, i, fex))
		{
			if (var_case(s[++i], new, &j, &i))
				continue ;
			copy(new, get_env_content(variable_name_geter(s + i)), &j);
			while (allowed_char(s[i]))
				i++;
		}
		else
			new[j++] = s[i++];
	}
	new[j] = '\0';
	return (new);
}
