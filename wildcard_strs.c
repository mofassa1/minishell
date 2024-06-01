/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_strs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 02:09:37 by afadouac          #+#    #+#             */
/*   Updated: 2024/03/21 02:42:33 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sorted(int *arr, int i)
{
	while (i > 0)
	{
		if (arr[i] < arr[i - 1])
			return (0);
		i--;
	}
	return (1);
}

int	is_doubled(int *str, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (str[j] == str[i])
			return (1);
		j++;
	}
	return (0);
}

int	is_sorted(char *str, char *cmd, char *file)
{
	int	i;
	int	len;
	int	f_len;

	i = 1;
	f_len = ft_strlen(file);
	len = ft_strlen(cmd);
	if (cmd[0] != '*' && str[0] != 0)
		return (0);
	if (cmd[len - 1] != '*')
		if (ft_strrcmp(cmd, file, len, f_len))
			return (0);
	while (str[i])
	{
		if (str[i] < str[i - 1])
			return (0);
		i++;
	}
	return (1);
}

int	ft_strrcmp(char *str1, char *str2, int len1, int len2)
{
	while (str1[len1] != '*')
	{
		if (str1[len1] != str2[len2])
			return (0);
		len1--;
		len2--;
	}
	return (1);
}

int	strings_count(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
