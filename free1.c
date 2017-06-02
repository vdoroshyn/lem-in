/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 18:50:11 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/06/02 18:50:22 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			free_inner(t_route *head)
{
	t_route		*tmp;

	while (head != NULL)
	{
		tmp = head;
		free(tmp);
		head = head->next;
	}
}

void			destroy_outer(t_a *abyss)
{
	t_way		*tmp;
	t_way		*tmp1;

	tmp = abyss->routes;
	while (tmp != NULL)
	{
		if (tmp->head != NULL)
		{
			free_inner(tmp->head);
			tmp->head = NULL;
			tmp->tail = NULL;
		}
		tmp1 = tmp;
		free(tmp1);
		tmp = tmp->next;
	}
	abyss->routes = NULL;
}

static int		is_in_list(t_temp *best, int num)
{
	while (best != NULL)
	{
		if (best->room_index == num)
		{
			return (1);
		}
		best = best->next;
	}
	return (0);
}

static void		free_outer(t_way *head, t_a *abyss)
{
	t_way *tmp;

	tmp = head;
	if (head->prev == NULL)
	{
		abyss->routes = head->next;
		if (head->next != NULL)
		{
			head->next->prev = NULL;
		}
	}
	else
	{
		head->prev->next = head->next;
		if (head->next != NULL)
		{
			head->next->prev = head->prev;
		}
	}
	free(tmp);
}

void			remove_odd_routes(t_a *abyss)
{
	t_way		*tmp;

	tmp = abyss->routes;
	while (tmp != NULL)
	{
		if (!is_in_list(abyss->best, tmp->num))
		{
			free_inner(tmp->head);
			tmp->head = NULL;
			tmp->tail = NULL;
			free_outer(tmp, abyss);
		}
		tmp = tmp->next;
	}
}
