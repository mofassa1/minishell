/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:31:58 by mezzine           #+#    #+#             */
/*   Updated: 2024/04/02 03:25:43 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (dstsize == 0 || ft_strlen(dst) >= dstsize)
		return (dstsize + ft_strlen(src));
	j = ft_strlen(dst);
	while (i < dstsize - j - 1 && src[i] != '\0')
	{
		dst[i + j] = src[i];
		i++;
	}
	dst[i + j] = '\0';
	return (j + ft_strlen(src));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	size_t	i;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (!s2 && s1)
		return (ft_strdup(s1));
	i = ft_strlen(s1) + ft_strlen(s2);
	s = ft_malloc(i + 1, 'm');
	if (!s)
		return (NULL);
	s[0] = '\0';
	ft_strlcat(s, s1, ft_strlen(s1) + 1);
	ft_strlcat(s, s2, i + 1);
	return (s);
}

char	**sts(t_strings *s, char *cmd)
{
	size_t	i;
	char	**v;

	i = 0;
	v = ft_malloc((ft_lstsize_strings(s) + 2) * sizeof(char **), 'm');
	v[i++] = cmd;
	while (s)
	{
		v[i] = s->str;
		i++;
		s = s->next;
	}
	v[i] = NULL;
	return (v);
}

char	*cmd_path(char *cmd)
{
	char	*tmp;
	char	*s;
	char	**paths;

	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/') || !get_env("PATH"))
		return (cmd);
	paths = ft_split(get_env_content("PATH"), ":");
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		s = ft_strjoin(tmp, cmd);
		if (!access(s, F_OK))
			return (s);
		paths++;
	}
	return (NULL);
}

char	*ft_strtrim(char *s)
{
	size_t	i;
	size_t	j;
	size_t	q;
	char	*new;

	if (!s)
		return (NULL);
	new = ft_malloc(ft_strlen(s) - nbr_of_quote(s) * 2 + 1, 'm');
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			q = i + 1;
			while (s[q] != s[i])
				new[j++] = s[q++];
			i = q + 1;
		}
		else
			new[j++] = s[i++];
	}
	new[j] = '\0';
	return (new);
}
