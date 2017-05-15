/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 16:38:40 by vdoroshy          #+#    #+#             */
/*   Updated: 2016/12/09 11:19:53 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memalloc(size_t size)
{
	void	*res;
	char	*ptr;
	size_t	i;

	res = malloc(size);
	if (res == NULL)
	{
		return (NULL);
	}
	i = 0;
	ptr = (char *)res;
	while (i < size)
	{
		ptr[i] = 0;
		i++;
	}
	return (res);
}
