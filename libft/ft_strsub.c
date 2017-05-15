/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 19:12:15 by vdoroshy          #+#    #+#             */
/*   Updated: 2016/12/06 12:32:35 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ptr;

	if (s == NULL)
	{
		return (NULL);
	}
	if ((ptr = ft_strnew(len)) != NULL)
	{
		ft_strncpy(ptr, &s[start], len);
		return (ptr);
	}
	return (NULL);
}
