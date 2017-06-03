/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rooms2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 17:55:41 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/06/03 17:55:49 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			room_to_list(char **line, t_a *abyss)
{
	t_lst		*temp;

	temp = (t_lst *)malloc(sizeof(t_lst));
	if (temp == NULL)
	{
		ft_strdel(line);
		c_destruct(abyss);
		write(1, "Not enough memory\n", 18);
		exit(-2);
	}
	temp->content = ft_strdup_delim(*line, ' ');
	if (temp->content == NULL)
	{
		ft_strdel(line);
		free(temp);
		c_destruct(abyss);
		write(1, "Not enough memory\n", 18);
		exit(-2);
	}
	coords_to_node(line, &temp->x, &temp->y, abyss);
	temp->next = abyss->head;
	abyss->head = temp;
	abyss->node_count += 1;
	ft_putendlstrdel(line);
}

static void		ft_read_rooms_norme(char **line, t_a *abyss)
{
	ft_strdel(line);
	destuctexit(abyss);
}

int				ft_read_rooms(char **line, t_a *abyss)
{
	while (get_next_line(0, line) > 0)
	{
		if (ft_strcmp(*line, "##start") == 0)
			check_start(line, abyss);
		else if (ft_strcmp(*line, "##end") == 0)
			check_end(line, abyss);
		else if (vd_strlen(*line) > 3 && (*line)[0] == '#' && (*line)[1] == '#')
		{
			if (other_commands(line, abyss))
				return (2);
		}
		else if ((*line)[0] == '#')
			ft_putendlstrdel(line);
		else if (room_validate(*line))
			room_to_list(line, abyss);
		else
		{
			if (abyss->start == NULL || abyss->end == NULL)
				ft_read_rooms_norme(line, abyss);
			return (1);
		}
	}
	return (0);
}
