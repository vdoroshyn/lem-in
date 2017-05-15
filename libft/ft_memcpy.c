/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 15:04:34 by vdoroshy          #+#    #+#             */
/*   Updated: 2016/12/06 12:08:07 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void						*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char			*ptr1;
	const unsigned char		*ptr2;

	ptr1 = (unsigned char *)dst;
	ptr2 = (unsigned char *)src;
	while (n != 0)
	{
		*ptr1 = *ptr2;
		n--;
		ptr1++;
		ptr2++;
	}
	return (dst);
}
