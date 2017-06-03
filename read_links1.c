/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_links1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 16:27:38 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/06/03 16:27:48 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		links_norme(char **line, t_a *abyss)
{
	if (!(link_validate(*line, abyss)))
	{
		ft_strdel(line);
		c_destruct(abyss);
		write(1, "ERROR\n", 6);
		exit(-4);
	}
	else
	{
		ft_putendlstrdel(line);
	}
}

static int		ft_check_links(char **line, t_a *abyss)
{
	if ((ft_strcmp("##start", *line) == 0) || (ft_strcmp("##end", *line) == 0))
	{
		ft_strdel(line);
		c_destruct(abyss);
		write(1, "ERROR\n", 6);
		exit(-4);
	}
	else if (vd_strlen(*line) > 3 && (*line)[0] == '#' && (*line)[1] == '#')
	{
		ft_putendlstrdel(line);
		if (get_next_line(0, line) > 0)
		{
			links_norme(line, abyss);
		}
	}
	else if ((*line)[0] == '#' || link_validate(*line, abyss))
	{
		ft_putendlstrdel(line);
	}
	else
	{
		return (0);
	}
	return (1);
}

int				ft_read_links(char **line, t_a *abyss)
{
	if (abyss->flag == 2)
	{
		if (!(link_validate(*line, abyss)))
		{
			ft_strdel(line);
			c_destruct(abyss);
			write(1, "ERROR\n", 6);
			exit(-4);
		}
		else
		{
			ft_putendlstrdel(line);
		}
	}
	else if (!ft_check_links(line, abyss))
	{
		return (0);
	}
	while (get_next_line(0, line) > 0)
	{
		if (!ft_check_links(line, abyss))
			return (0);
	}
	return (1);
}
