/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 16:49:00 by vdoroshy          #+#    #+#             */
/*   Updated: 2016/12/05 12:42:49 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	int		i;

	i = (int)ft_strlen(s);
	if (c == '\0')
	{
		return (char *)(&(s[i]));
	}
	i = i - 1;
	while (i >= 0)
	{
		if (s[i] == c)
		{
			return (char *)(&(s[i]));
		}
		i--;
	}
	return (NULL);
}
