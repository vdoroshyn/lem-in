/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_delim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 14:13:49 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/06/03 14:13:55 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup_delim(const char *s1, char c)
{
	char	*s2;
	int		i;

	s2 = (char *)malloc(vd_strlen_delim(s1, c) * (sizeof(char) + 1));
	if (s2 == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (s1[i] != c)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
