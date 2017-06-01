/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aug_lib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 17:06:10 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/04/27 17:06:23 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			ft_strlen_space(const char *s)
{
	int		i;

	i = 0;
	while (s[i] != ' ')
	{
		i++;
	}
	return (i);
}

char		*ft_strdup_space(const char *s1)
{
	char	*s2;
	int		i;

	s2 = (char *)malloc(ft_strlen_space(s1) * (sizeof(char) + 1));
	if (s2 == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (s1[i] != ' ')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

int			ft_isprint_nospace(char c)
{
	if (c > 32 && c <= 126 && c != 45)
	{
		return (1);
	}
	return (0);
}

int			vd_strlen(const char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
