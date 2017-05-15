/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:28:56 by vdoroshy          #+#    #+#             */
/*   Updated: 2016/12/05 17:37:21 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*head;
	t_list	*current;

	if (lst == NULL || f == NULL)
	{
		return (NULL);
	}
	current = (*f)(lst);
	head = current;
	while (lst->next != NULL)
	{
		lst = lst->next;
		current->next = (*f)(lst);
		if (current->next == NULL)
		{
			return (NULL);
		}
		current = current->next;
	}
	return (head);
}
