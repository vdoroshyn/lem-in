/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 15:05:00 by vdoroshy          #+#    #+#             */
/*   Updated: 2016/12/06 10:48:07 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*temp;

	temp = (t_list *)malloc(sizeof(t_list));
	if (temp == NULL)
	{
		return (NULL);
	}
	if (content == NULL)
	{
		temp->content = NULL;
		temp->content_size = 0;
		temp->next = NULL;
		return (temp);
	}
	temp->content = malloc(content_size);
	if (temp->content == NULL)
	{
		free(temp);
		return (NULL);
	}
	ft_memcpy(temp->content, content, content_size);
	temp->content_size = content_size;
	temp->next = NULL;
	return (temp);
}
