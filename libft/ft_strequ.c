/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 16:45:15 by vdoroshy          #+#    #+#             */
/*   Updated: 2016/12/02 11:39:40 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	if (s1 == NULL && s2 == NULL)
	{
		return (1);
	}
	if (s1 == NULL || s2 == NULL)
	{
		return (0);
	}
	if (ft_strcmp(s1, s2) == 0)
	{
		return (1);
	}
	return (0);
}
