/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 19:19:18 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/06/01 19:19:40 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**a lot of places
*/

void		ft_putendlstrdel(char **line)
{
	ft_putendl(*line);
	ft_strdel(line);
}

/*
**ants validation
*/

int			ft_ants_atoi(const char *str)
{
	int		res;
	int		i;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > 214748364 || (res == 214748364 && str[i] > '6'))
		{
			return (0);
		}
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

/*
**ants movement
*/

void		add_route_priority(t_way *head)
{
	int		len_0;
	int		i;

	len_0 = head->size;
	i = 0;
	while (head != NULL)
	{
		head->stop = (head->size - len_0) + (i - 1);
		++i;
		head = head->next;
	}
}
