/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 19:06:51 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/06/02 19:06:59 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		new_route_norme(t_a *abyss, t_route *tmp1)
{
	if (tmp1 == NULL)
	{
		c_destruct(abyss);
		write(1, "Not enough memory\n", 18);
		exit(-5);
	}
}

void			new_route_emerges(t_a *abyss, int size)
{
	t_route		*tmp1;
	t_temp		*tmp2;

	tmp2 = abyss->test_route;
	while (size != 0)
	{
		tmp1 = new_room();
		new_route_norme(abyss, tmp1);
		if (abyss->routes->head == NULL)
		{
			tmp1->room_index = tmp2->room_index;
			abyss->routes->tail = tmp1;
			abyss->routes->head = tmp1;
		}
		else
		{
			tmp1->room_index = tmp2->room_index;
			abyss->routes->head->prev = tmp1;
			tmp1->next = abyss->routes->head;
			abyss->routes->head = tmp1;
		}
		tmp2 = tmp2->next;
		size--;
	}
}

void			create_a_route(t_a *abyss, int size)
{
	t_way		*node;

	node = create_way_node(size);
	if (node == NULL)
	{
		c_destruct(abyss);
		write(1, "Not enough memory\n", 18);
		exit(-5);
	}
	if (abyss->routes == NULL)
	{
		abyss->routes = node;
	}
	else
	{
		abyss->routes->prev = node;
		node->next = abyss->routes;
		abyss->routes = node;
	}
	new_route_emerges(abyss, size);
}

static int		backtracking(t_a *abyss, int index, int *size)
{
	int			i;

	*size += 1;
	add_to_temp_list(abyss, index);
	if (index == abyss->node_count - 1)
	{
		create_a_route(abyss, *size);
		return (0);
	}
	i = 0;
	while (i < abyss->node_count)
	{
		if (abyss->matrix[index][i] == 1 && abyss->visit[i] == 0)
		{
			abyss->visit[i] = 1;
			backtracking(abyss, i, size);
			free_temp_node(abyss);
			abyss->visit[i] = 0;
			*size -= 1;
		}
		i++;
	}
	return (1);
}

void			finding_path(t_a *abyss)
{
	int			size;

	size = 0;
	abyss->visit = ft_intnew(abyss->node_count);
	if (abyss->visit == NULL)
	{
		c_destruct(abyss);
		write(1, "Not enough memory\n", 18);
		exit(-5);
	}
	abyss->visit[0] = 1;
	backtracking(abyss, 0, &size);
	abyss->visit[0] = 0;
	free_temp_node(abyss);
}
