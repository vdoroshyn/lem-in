/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 16:14:07 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/05/04 16:14:15 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_2d_array(void **arr, int elem_count)
{
	int i;

	i = 0;
	while (i < elem_count)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}
