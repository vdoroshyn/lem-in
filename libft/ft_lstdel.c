/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 14:17:29 by vdoroshy          #+#    #+#             */
/*   Updated: 2016/12/06 10:56:50 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*temp_next;

	if (alst != NULL && *alst != NULL && del != NULL)
	{
		while (*alst != NULL)
		{
			temp_next = (*alst)->next;
			ft_lstdelone(alst, (*del));
			*alst = temp_next;
		}
	}
}
