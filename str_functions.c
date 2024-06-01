/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:38:09 by afadouac          #+#    #+#             */
/*   Updated: 2024/03/21 02:39:11 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return (i);
		i--;
	}
	return (-1);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strdup_original(const char *s1)
{
	char	*c;
	size_t	i;

	if (!s1)
		return (NULL);
	i = ft_strlen(s1);
	c = malloc(i + 1);
	if (c == NULL)
		return (c);
	ft_strlcpy(c, s1, i + 1);
	return (c);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*c;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup_original(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	c = malloc(len + 1);
	if (!c)
		return (NULL);
	ft_strlcpy(c, s + start, len + 1);
	return (c);
}

char	*ft_strjoin_or(char const *s1, char const *s2)
{
	char	*s;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	s = malloc(i + 1);
	if (!s)
		return (NULL);
	s[0] = '\0';
	ft_strlcat(s, s1, ft_strlen(s1) + 1);
	ft_strlcat(s, s2, i + 1);
	return (s);
}
