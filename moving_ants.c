/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_ants.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 20:07:33 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/06/01 20:07:44 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		push_ants(t_a *abyss, t_route *tail)
{
	int			flag;

	flag = 0;
	tail->ant_num = 0;
	while (tail->prev->prev != NULL)
	{
		if (tail->prev->ant_num != 0)
		{
			tail->ant_num = tail->prev->ant_num;
			if (abyss->len == 0)
			{
				write(1, "L", 1);
				abyss->len = 1;
			}
			else
				write(1, " L", 2);
			ft_putnbr(tail->ant_num);
			write(1, "-", 1);
			ft_putstr(abyss->names[tail->room_index]);
			tail->prev->ant_num = 0;
			++flag;
		}
		tail = tail->prev;
	}
	return (flag);
}

static int		push_new_ants(t_a *abyss, t_route *head)
{
	int			flag;

	flag = 0;
	if (head->ant_num != 0)
	{
		head->next->ant_num = head->ant_num;
		if (abyss->len == 0)
		{
			write(1, "L", 1);
			abyss->len = 1;
		}
		else
		{
			write(1, " L", 2);
		}
		ft_putnbr(head->ant_num);
		write(1, "-", 1);
		ft_putstr(abyss->names[head->next->room_index]);
		head->ant_num = 0;
		++flag;
	}
	return (flag);
}

static int		push_to_start(t_a *abyss, int *i, t_way *tmp)
{
	int			flag;

	flag = 0;
	if (*i <= abyss->ants && (abyss->ants - *i + 1) >= tmp->stop)
	{
		tmp->head->ant_num = *i;
		*i += 1;
		++flag;
	}
	return (flag);
}

static void		ants_move_initialize(t_a *abyss, int *i)
{
	*i = 1;
	abyss->flag = 1;
	abyss->len = 0;
}

void			moving_ants(t_a *abyss)
{
	t_way		*tmp;
	int			i;

	add_route_priority(abyss->routes);
	ants_move_initialize(abyss, &i);
	while (abyss->flag != 0)
	{
		abyss->flag = 0;
		tmp = abyss->routes;
		while (tmp != NULL)
		{
			abyss->flag += push_ants(abyss, tmp->tail);
			tmp = tmp->next;
		}
		tmp = abyss->routes;
		while (tmp != NULL)
		{
			abyss->flag += push_new_ants(abyss, tmp->head);
			abyss->flag += push_to_start(abyss, &i, tmp);
			tmp = tmp->next;
		}
		if (abyss->flag != 0)
			write(1, "\n", 1);
		abyss->len = 0;
	}
}
