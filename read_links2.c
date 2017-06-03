/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_links2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 16:38:22 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/06/03 16:38:47 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		only_one_hyphen(char *line)
{
	int			i;
	int			flag;

	flag = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '-')
		{
			++flag;
		}
		++i;
	}
	if (flag != 1)
	{
		return (0);
	}
	return (1);
}

static int		ft_hyphen(char *line)
{
	int			i;
	int			j;

	if (!only_one_hyphen(line))
		return (0);
	i = 0;
	while (line[i] != '-')
	{
		++i;
	}
	if (i == 0)
	{
		return (0);
	}
	++i;
	j = i;
	while (line[j] != '\0')
	{
		j++;
	}
	if (j - i == 0)
	{
		return (0);
	}
	return (1);
}

static int		search_word(char *str, t_a *abyss)
{
	int			i;

	i = 0;
	while (i < abyss->node_count)
	{
		if (!ft_strcmp(abyss->names[i], str))
		{
			return (i);
		}
		++i;
	}
	return (-1);
}

static int		words_to_matrix(char *str1, char *str2, t_a *abyss)
{
	int			i;
	int			j;

	i = search_word(str1, abyss);
	j = search_word(str2, abyss);
	if (i == -1 || j == -1)
	{
		return (0);
	}
	if (abyss->matrix[i][j] == 1 || abyss->matrix[j][i] == 1)
	{
		return (0);
	}
	abyss->matrix[i][j] = 1;
	abyss->matrix[j][i] = 1;
	return (1);
}

int				link_validate(char *line, t_a *abyss)
{
	char		*str1;
	char		*str2;
	int			i;

	if (!ft_hyphen(line))
		return (0);
	if (!(str1 = ft_strdup_delim(line, '-')))
		return (0);
	i = 0;
	while (line[i] != '-')
		++i;
	++i;
	if (!(str2 = ft_strdup_delim(&line[i], '\0')))
	{
		ft_strdel(&str1);
		return (0);
	}
	if (!ft_strcmp(str1, str2))
		return (0);
	if (!words_to_matrix(str1, str2, abyss))
		return (0);
	ft_strdel(&str1);
	ft_strdel(&str2);
	return (1);
}
