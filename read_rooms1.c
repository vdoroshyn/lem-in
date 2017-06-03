/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rooms1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 17:55:30 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/06/03 17:55:37 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		ft_coords_atoi(const char *str)
{
	int			res;
	int			i;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > 214748364 || (res == 214748364 && str[i] > '7'))
		{
			return (-1);
		}
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

void			coords_to_node(char **line, int *x, int *y, t_a *abyss)
{
	int			i;

	i = 0;
	while ((*line)[i] != ' ')
	{
		i++;
	}
	i++;
	*x = ft_coords_atoi(&(*line)[i]);
	if (*x == -1)
	{
		ft_strdel(line);
		destuctexit(abyss);
	}
	while ((*line)[i] != ' ')
	{
		i++;
	}
	i++;
	*y = ft_coords_atoi(&(*line)[i]);
	if (*y == -1)
	{
		ft_strdel(line);
		destuctexit(abyss);
	}
}

static int		search_for_two_spaces(char *line)
{
	int			i;
	int			space;

	i = 0;
	space = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
		{
			space++;
		}
		i++;
	}
	if (space == 2)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

static int		room_validate_norme(char *line, int *i)
{
	*i = 0;
	while (line[*i] != ' ')
	{
		if (!ft_isprint_nospace(line[*i]))
		{
			return (0);
		}
		*i += 1;
	}
	*i += 1;
	while (line[*i] != ' ')
	{
		if (!ft_isdigit(line[*i]))
		{
			return (0);
		}
		*i += 1;
	}
	*i += 1;
	return (1);
}

int				room_validate(char *line)
{
	int			i;
	int			flag;

	if (line[0] == '#' || line[0] == '\0' || line[0] == 'L'
		|| !search_for_two_spaces(line))
	{
		return (0);
	}
	if (!room_validate_norme(line, &i))
	{
		return (0);
	}
	flag = 0;
	while (line[i] != '\0')
	{
		if (!ft_isdigit(line[i]))
		{
			return (0);
		}
		++i;
		++flag;
	}
	if (flag == 0)
		return (0);
	return (1);
}
