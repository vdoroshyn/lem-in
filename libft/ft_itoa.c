/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 12:13:10 by vdoroshy          #+#    #+#             */
/*   Updated: 2016/12/06 11:07:11 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	int_length(int n)
{
	size_t		length;

	if (n == -2147483648)
	{
		return (11);
	}
	if (n == 0)
	{
		return (1);
	}
	length = 0;
	if (n < 0)
	{
		length++;
	}
	while (n != 0)
	{
		n = n / 10;
		length++;
	}
	return (length);
}

char			*ft_itoa(int n)
{
	char		*ptr;
	size_t		length;

	length = int_length(n);
	ptr = ft_strnew(length);
	if (ptr == NULL)
		return (NULL);
	if (n == 0)
		ptr[0] = '0';
	if (n == -2147483648)
		return (ft_strcpy(ptr, "-2147483648"));
	if (n < 0)
	{
		ptr[0] = '-';
		n = n * -1;
	}
	while (n != 0)
	{
		ptr[length - 1] = (n % 10) + '0';
		length--;
		n = n / 10;
	}
	return (ptr);
}
