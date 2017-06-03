/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 17:20:42 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/04/20 17:20:47 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		validation(t_a *abyss, char **line)
{
	ft_read_ants(line, abyss);
	if (!(abyss->flag = ft_read_rooms(line, abyss)))
		destuctexit(abyss);
	start_end_to_list(abyss);
	validate_room_names_coords(abyss, line);
	if (!matrix_init(abyss))
	{
		c_destruct(abyss);
		write(1, "Not enough memory\n", 18);
		exit(-3);
	}
	if (!names_init(abyss))
	{
		c_destruct(abyss);
		write(1, "Not enough memory\n", 18);
		exit(-3);
	}
	if (!ft_read_links(line, abyss))
	{
		ft_strdel(line);
		c_destruct(abyss);
		write(1, "ERROR\n", 6);
		exit(-4);
	}
}

static void		algorithm(t_a *abyss)
{
	finding_path(abyss);
	if (abyss->routes == NULL)
	{
		write(1, "ERROR\n", 6);
		exit(-4);
	}
	sorting_routes(abyss);
	set_search(abyss->routes, abyss);
	remove_odd_routes(abyss);
	moving_ants(abyss);
}

int				main(void)
{
	char		*line;
	t_a			abyss;

	c_construct(&abyss, &line);
	validation(&abyss, &line);
	algorithm(&abyss);
	c_destruct(&abyss);
	return (0);
}
