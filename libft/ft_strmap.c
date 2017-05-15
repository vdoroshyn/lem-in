/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 16:33:51 by vdoroshy          #+#    #+#             */
/*   Updated: 2016/12/01 16:01:58 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	char	*ptr;
	size_t	i;

	if (s == NULL || f == NULL)
	{
		return (NULL);
	}
	ptr = ft_strnew(ft_strlen(s));
	if (ptr == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (s[i] != '\0')
	{
		ptr[i] = (*f)(s[i]);
		i++;
	}
	return (ptr);
}
