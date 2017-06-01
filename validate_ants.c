/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_ants.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 14:18:23 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/04/28 14:18:33 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		ants_num_validate(char **line)
{
	int			i;

	i = 0;
	while ((*line)[i] != '\0')
	{
		if (ft_isdigit((*line)[i]))
		{
			i++;
		}
		else
		{
			i = -1;
			break ;
		}
	}
	if (vd_strlen(*line) == 0 || i == -1)
	{
		ft_strdel(line);
		write(1, "ERROR\n", 6);
		exit(-1);
	}
}

static void		get_ants(char **line, t_a *abyss)
{
	ants_num_validate(line);
	abyss->ants = ft_ants_atoi(*line);
	ft_putendlstrdel(line);
}

static void		ant_commands(char **line, t_a *abyss)
{
	ft_putendlstrdel(line);
	if (get_next_line(0, line) > 0)
	{
		get_ants(line, abyss);
		return ;
	}
	else
	{
		write(1, "ERROR\n", 6);
		exit(-1);
	}
}

static void		error_ant_start(char **line)
{
	if ((ft_strcmp("##start", *line) == 0)
		|| (ft_strcmp("##end", *line) == 0))
	{
		ft_strdel(line);
		write(1, "ERROR\n", 6);
		exit(-1);
	}
}

void			ft_read_ants(char **line, t_a *abyss)
{
	int			i;

	i = 0;
	while (get_next_line(0, line) > 0)
	{
		i++;
		error_ant_start(line);
		if (vd_strlen(*line) > 3 && (*line)[0] == '#' && (*line)[1] == '#')
		{
			ant_commands(line, abyss);
			break ;
		}
		else if ((*line)[0] == '#')
			ft_putendlstrdel(line);
		else
		{
			get_ants(line, abyss);
			break ;
		}
	}
	if (i == 0 || abyss->ants == 0)
	{
		write(1, "ERROR\n", 6);
		exit(-1);
	}
}
