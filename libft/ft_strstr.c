/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 13:30:45 by vdoroshy          #+#    #+#             */
/*   Updated: 2016/11/30 17:57:04 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *big, const char *little)
{
	size_t	len;

	if (*little == '\0')
	{
		return (char *)(big);
	}
	len = ft_strlen(little);
	while (*big != '\0')
	{
		if (*big == *little)
		{
			if (ft_strncmp(big, little, len) == 0)
			{
				return (char *)(big);
			}
		}
		big++;
	}
	return (NULL);
}
