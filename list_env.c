/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 21:55:09 by afadouac          #+#    #+#             */
/*   Updated: 2024/04/01 18:17:29 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_clear(void)
{
	t_env	*tmp;

	while (*get_env_list())
	{
		tmp = *get_env_list();
		*get_env_list() = (*get_env_list())->next;
		free(tmp->content);
		free(tmp->variable);
		free(tmp);
	}
	*get_env_list() = NULL;
	free(*get_pwdpath());
	*get_pwdpath() = NULL;
}

int	env_lstsize(t_env *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_env	*env_lstlast(t_env *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

t_env	*ft_lstnew_env(char *name, char *content)
{
	t_env	*n;

	n = malloc(sizeof(t_env));
	if (!n)
		return (NULL);
	n->variable = ft_strdup_original(name);
	n->content = ft_strdup_original(content);
	n->next = NULL;
	return (n);
}

void	env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (lst)
	{
		if (!*lst)
		{
			*lst = new;
			return ;
		}
		last = env_lstlast(*lst);
		last->next = new;
	}
}
