/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_destruct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 18:25:53 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/06/03 18:26:00 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		c_destruct1(t_a *abyss)
{
	if (abyss->visit != NULL)
	{
		free(abyss->visit);
		abyss->visit = NULL;
	}
	if (abyss->test_route != NULL)
	{
		free_temp_list(abyss);
	}
	if (abyss->best != NULL)
	{
		free_best(abyss);
	}
	if (abyss->routes != NULL)
	{
		destroy_outer(abyss);
	}
}

void			c_destruct(t_a *abyss)
{
	if (abyss->matrix != NULL)
	{
		free_2d_array((void **)abyss->matrix, abyss->node_count);
		abyss->matrix = NULL;
	}
	if (abyss->names != NULL)
	{
		free_2d_array((void **)abyss->names, abyss->node_count);
		abyss->names = NULL;
	}
	if (abyss->head != NULL)
	{
		free_list(abyss);
	}
	if (abyss->end != NULL)
	{
		free_end_start(&abyss->end);
	}
	if (abyss->start != NULL)
	{
		free_end_start(&abyss->start);
	}
	c_destruct1(abyss);
}

void			c_construct(t_a *abyss, char **line)
{
	abyss->head = NULL;
	abyss->start = NULL;
	abyss->end = NULL;
	abyss->ants = 0;
	abyss->node_count = 2;
	*line = NULL;
	abyss->flag = 0;
	abyss->routes = NULL;
	abyss->test_route = NULL;
	abyss->visit = NULL;
	abyss->best = NULL;
	abyss->priority = 0;
	abyss->matrix = NULL;
	abyss->names = NULL;
}
