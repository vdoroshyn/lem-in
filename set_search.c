/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 18:33:00 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/06/02 18:33:11 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		ft_isunique(t_route *tmp, t_a *abyss)
{
	while (tmp != NULL)
	{
		if (tmp->room_index != 0 && tmp->room_index != abyss->node_count - 1)
		{
			if (abyss->visit[tmp->room_index] == 1)
			{
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

static void		rooms_to_visit(t_route *tmp, t_a *abyss)
{
	while (tmp != NULL)
	{
		if (tmp->room_index != 0 && tmp->room_index != abyss->node_count - 1)
		{
			abyss->visit[tmp->room_index] = 1;
		}
		tmp = tmp->next;
	}
}

static void		visit_to_zero(int *ptr, int size)
{
	int			i;

	i = 0;
	while (i < size)
	{
		ptr[i] = 0;
		i++;
	}
}

static void		choosing_best_outta_two(t_a *abyss, int num)
{
	float		res;

	res = (float)(abyss->ants + num) / (float)abyss->len;
	if (abyss->priority == 0 || res < abyss->priority)
	{
		abyss->priority = res;
		if (abyss->best != NULL)
		{
			free_best(abyss);
		}
		abyss->best = abyss->test_route;
		abyss->test_route = NULL;
	}
	else
	{
		free_temp_list(abyss);
	}
}

void			set_search(t_way *head, t_a *abyss)
{
	t_way		*tmp;
	int			num;

	while (head != NULL)
	{
		abyss->len = 0;
		num = 0;
		tmp = head;
		while (tmp != NULL)
		{
			if (ft_isunique(tmp->head, abyss))
			{
				rooms_to_visit(tmp->head, abyss);
				route_to_tempset(tmp->num, abyss);
				num += tmp->size - 1;
				abyss->len += 1;
			}
			tmp = tmp->next;
		}
		choosing_best_outta_two(abyss, num);
		visit_to_zero(abyss->visit, abyss->node_count);
		head = head->next;
	}
}
