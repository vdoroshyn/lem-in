/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 15:30:58 by vdoroshy          #+#    #+#             */
/*   Updated: 2016/12/02 15:44:34 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *b, const char *l, size_t len)
{
	size_t	length;

	if (*l == '\0')
	{
		return (char *)(b);
	}
	length = ft_strlen(l);
	while (len != 0 && *b != '\0')
	{
		if (*b == *l)
		{
			if (len >= length)
			{
				if (ft_strncmp(b, l, length) == 0)
				{
					return (char *)(b);
				}
			}
		}
		len--;
		b++;
	}
	return (NULL);
}
