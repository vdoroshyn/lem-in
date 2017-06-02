/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_nodes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 19:36:52 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/06/02 19:37:00 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_temp		*create_temp_node(int index)
{
	t_temp	*node;

	node = (t_temp *)malloc(sizeof(t_temp));
	if (node == NULL)
	{
		return (node);
	}
	node->room_index = index;
	node->next = NULL;
	return (node);
}

void		add_to_temp_list(t_a *abyss, int index)
{
	t_temp	*node;

	node = create_temp_node(index);
	if (node == NULL)
	{
		c_destruct(abyss);
		write(1, "Not enough memory\n", 18);
		exit(-5);
	}
	node->next = abyss->test_route;
	abyss->test_route = node;
}

t_way		*create_way_node(int size)
{
	t_way	*node;

	node = (t_way *)malloc(sizeof(t_way));
	if (node == NULL)
	{
		return (node);
	}
	node->size = size;
	node->prev = NULL;
	node->next = NULL;
	node->head = NULL;
	node->tail = NULL;
	return (node);
}

t_route		*new_room(void)
{
	t_route *node;

	node = (t_route *)malloc(sizeof(t_route));
	if (node == NULL)
	{
		return (node);
	}
	node->prev = NULL;
	node->next = NULL;
	node->ant_num = 0;
	return (node);
}
