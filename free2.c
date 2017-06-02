/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 18:58:00 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/06/02 18:58:08 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		free_best(t_a *abyss)
{
	t_temp	*tmp;

	while (abyss->best != NULL)
	{
		tmp = abyss->best;
		abyss->best = abyss->best->next;
		free(tmp);
	}
	abyss->best = NULL;
}

void		free_temp_list(t_a *abyss)
{
	t_temp	*tmp;

	while (abyss->test_route != NULL)
	{
		tmp = abyss->test_route;
		abyss->test_route = abyss->test_route->next;
		free(tmp);
	}
	abyss->test_route = NULL;
}

void		free_end_start(t_lst **head)
{
	free((*head)->content);
	free(*head);
	*head = NULL;
}

void		free_list(t_a *abyss)
{
	t_lst	*temp;

	while (abyss->head != NULL)
	{
		temp = abyss->head->next;
		free(abyss->head->content);
		free(abyss->head);
		abyss->head = temp;
	}
	abyss->head = NULL;
	abyss->start = NULL;
	abyss->end = NULL;
}

void		free_temp_node(t_a *abyss)
{
	t_temp	*tmp;

	if (abyss->test_route != NULL && abyss->test_route->next != NULL)
	{
		tmp = abyss->test_route;
		abyss->test_route = abyss->test_route->next;
		free(tmp);
	}
	else if (abyss->test_route != NULL)
	{
		free(abyss->test_route);
		abyss->test_route = NULL;
	}
}
