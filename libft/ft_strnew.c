/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 10:27:53 by vdoroshy          #+#    #+#             */
/*   Updated: 2016/11/30 18:01:48 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnew(size_t size)
{
	char	*ptr;
	size_t	i;

	ptr = (char *)malloc(sizeof(char) * size + 1);
	if (ptr == NULL)
	{
		return (NULL);
	}
	ptr[size] = '\0';
	i = 0;
	while (size != 0)
	{
		ptr[i] = '\0';
		size--;
		i++;
	}
	return (ptr);
}
