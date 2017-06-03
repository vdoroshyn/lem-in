/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_room_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 17:39:01 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/06/03 17:39:08 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				other_commands(char **line, t_a *abyss)
{
	ft_putendlstrdel(line);
	get_next_line(0, line);
	if (*line != NULL && room_validate(*line))
	{
		room_to_list(line, abyss);
		ft_strdel(line);
		return (0);
	}
	else if (*line == NULL)
	{
		c_destruct(abyss);
		write(1, "ERROR\n", 6);
		exit(-2);
	}
	else
	{
		return (1);
	}
}

static void		check_start_norme(t_a *abyss, char **line)
{
	abyss->start = (t_lst *)malloc(sizeof(t_lst));
	if (abyss->start == NULL)
	{
		ft_strdel(line);
		c_destruct(abyss);
		write(1, "Not enough memory\n", 18);
		exit(-2);
	}
	abyss->start->content = ft_strdup_delim(*line, ' ');
	if (abyss->start->content == NULL)
	{
		ft_strdel(line);
		free(abyss->start);
		abyss->start = NULL;
		c_destruct(abyss);
		write(1, "Not enough memory\n", 18);
		exit(-2);
	}
}

void			check_start(char **line, t_a *abyss)
{
	if (abyss->start != NULL)
	{
		ft_strdel(line);
		destuctexit(abyss);
	}
	ft_putendlstrdel(line);
	get_next_line(0, line);
	if (*line != NULL && room_validate(*line))
	{
		check_start_norme(abyss, line);
		coords_to_node(line, &abyss->start->x, &abyss->start->y, abyss);
		abyss->start->next = NULL;
		ft_putendlstrdel(line);
	}
	else
	{
		ft_strdel(line);
		destuctexit(abyss);
	}
}

static void		check_end_norme(t_a *abyss, char **line)
{
	abyss->end = (t_lst *)malloc(sizeof(t_lst));
	if (abyss->end == NULL)
	{
		ft_strdel(line);
		c_destruct(abyss);
		write(1, "Not enough memory\n", 18);
		exit(-2);
	}
	abyss->end->content = ft_strdup_delim(*line, ' ');
	if (abyss->end->content == NULL)
	{
		ft_strdel(line);
		free(abyss->end);
		abyss->end = NULL;
		c_destruct(abyss);
		write(1, "Not enough memory\n", 18);
		exit(-2);
	}
}

void			check_end(char **line, t_a *abyss)
{
	if (abyss->end != NULL)
	{
		ft_strdel(line);
		destuctexit(abyss);
	}
	ft_putendlstrdel(line);
	get_next_line(0, line);
	if (*line != NULL && room_validate(*line))
	{
		check_end_norme(abyss, line);
		coords_to_node(line, &abyss->end->x, &abyss->end->y, abyss);
		abyss->end->next = NULL;
		ft_putendlstrdel(line);
	}
	else
	{
		ft_strdel(line);
		destuctexit(abyss);
	}
}
