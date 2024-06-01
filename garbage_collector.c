/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:57:16 by afadouac          #+#    #+#             */
/*   Updated: 2024/03/25 21:58:07 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_collect	*ft2_lstnew(void *ptr)
{
	t_collect	*new_collect;

	new_collect = malloc(sizeof(t_collect));
	if (!new_collect)
		return (NULL);
	new_collect->ptr = ptr;
	new_collect->next = NULL;
	return (new_collect);
}

void	ft2_lstadd_back(t_collect **lst, t_collect *new)
{
	static t_collect	*last;

	if (lst)
	{
		if (!*lst)
		{
			*lst = new;
			last = new;
			return ;
		}
		last->next = new;
		last = new;
	}
}

void	*ft_malloc(size_t size, char job)
{
	static t_collect	*collect;
	void				*ptr;
	t_collect			*tmp;

	if (job == 'f')
	{
		while (collect)
		{
			tmp = collect;
			collect = collect->next;
			free(tmp->ptr);
			free(tmp);
		}
		collect = NULL;
		return (NULL);
	}
	ptr = malloc(size);
	ft2_lstadd_back(&collect, ft2_lstnew(ptr));
	return (ptr);
}
