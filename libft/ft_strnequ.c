/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:49:22 by vdoroshy          #+#    #+#             */
/*   Updated: 2016/12/02 11:41:48 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (s1 == NULL && s2 == NULL)
	{
		return (1);
	}
	if (s1 == NULL || s2 == NULL)
	{
		return (0);
	}
	if (ft_strncmp(s1, s2, n) == 0)
	{
		return (1);
	}
	return (0);
}
