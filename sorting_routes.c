/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_routes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 20:29:34 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/06/01 20:29:43 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		number_nodes(t_a *abyss)
{
	t_way		*tmp;
	int			i;

	i = 0;
	tmp = abyss->routes;
	while (tmp != NULL)
	{
		tmp->num = i;
		i++;
		tmp = tmp->next;
	}
}

static void		inner_while(t_a *abyss, int *arr, t_way *temp, t_way *inner)
{
	while (inner != NULL && inner->next != NULL)
	{
		arr[0] = 0;
		if (inner->size > inner->next->size)
		{
			arr[1] += 1;
			if (inner->prev == NULL)
				abyss->routes = inner->next;
			if (inner->next->next != NULL)
				inner->next->next->prev = inner;
			temp = inner->next->next;
			inner->next->next = inner->next->prev;
			inner->next->prev = inner->prev;
			if (inner->prev != NULL)
				inner->prev->next = inner->next;
			inner->prev = inner->next;
			inner->next = temp;
			arr[0] = 1;
		}
		if (arr[0] == 0)
		{
			inner = inner->next;
		}
	}
}

void			sorting_routes(t_a *abyss)
{
	t_way		*temp;
	int			arr[2];

	temp = NULL;
	while (1)
	{
		arr[1] = 0;
		inner_while(abyss, arr, temp, abyss->routes);
		if (arr[1] == 0)
		{
			break ;
		}
	}
	number_nodes(abyss);
}
