/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 16:19:24 by vdoroshy          #+#    #+#             */
/*   Updated: 2016/12/06 11:14:52 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)dst;
	ptr2 = (unsigned char *)src;
	while (n != 0)
	{
		if ((*ptr1 = *ptr2) == (unsigned char)c)
		{
			ptr1++;
			return (void *)(ptr1);
		}
		n--;
		ptr1++;
		ptr2++;
	}
	return (NULL);
}
