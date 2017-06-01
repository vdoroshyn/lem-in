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

void			inner_while(t_a *abyss, int *swap, t_way *temp, t_way *inner)
{
	int			flag;

	while (inner != NULL && inner->next != NULL)
	{
		flag = 0;
		if (inner->size > inner->next->size)
		{
			*swap += 1;
			if (inner->prev == NULL)
			{
				abyss->routes = inner->next;
			}
			if (inner->next->next != NULL)
			{
				inner->next->next->prev = inner;
			}
			temp = inner->next->next;
			inner->next->next = inner->next->prev;
			inner->next->prev = inner->prev;
			if (inner->prev != NULL)
			{
				inner->prev->next = inner->next;
			}
			inner->prev = inner->next;
			inner->next = temp;
			flag = 1;
		}
		if (flag == 0)
		{
			inner = inner->next;
		}
	}
}

void			sorting_routes(t_a *abyss)
{
	t_way		*temp;
	// t_way		*inner;
	// int			flag;
	//int			swap;
	int arr[2];//arr[0] == flag, arr[1] == swap;

	temp = NULL;
	while (1)
	{
		swap = 0;
		inner_while(abyss, arr, temp, abyss->routes);
		// inner = abyss->routes;
		// while (inner != NULL && inner->next != NULL)
		// {
		// 	flag = 0;
		// 	if (inner->size > inner->next->size)
		// 	{
		// 		swap += 1;
		// 		if (inner->prev == NULL)
		// 		{
		// 			abyss->routes = inner->next;
		// 		}
		// 		if (inner->next->next != NULL)
		// 		{
		// 			inner->next->next->prev = inner;
		// 		}
		// 		temp = inner->next->next;
		// 		inner->next->next = inner->next->prev;
		// 		inner->next->prev = inner->prev;
		// 		if (inner->prev != NULL)
		// 		{
		// 			inner->prev->next = inner->next;
		// 		}
		// 		inner->prev = inner->next;
		// 		inner->next = temp;
		// 		flag = 1;
		// 	}
		// 	if (flag == 0)
		// 	{
		// 		inner = inner->next;
		// 	}
		//}
		if (swap == 0)
		{
			break ;
		}
	}
	number_nodes(abyss);
}
