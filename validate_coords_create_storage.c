/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_coords_create_storage.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 17:08:27 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/06/03 17:08:37 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		start_end_to_list(t_a *abyss)
{
	t_lst	*temp;

	temp = abyss->head;
	if (temp != NULL)
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = abyss->end;
	}
	else
	{
		abyss->head = abyss->end;
	}
	abyss->start->next = abyss->head;
	abyss->head = abyss->start;
}

void		validate_room_names_coords(t_a *abyss, char **line)
{
	t_lst	*temp;
	t_lst	*temp1;

	temp = abyss->head;
	while (temp->next != NULL)
	{
		abyss->len = vd_strlen(temp->content);
		temp1 = temp->next;
		while (temp1 != NULL)
		{
			if ((ft_strcmp(temp->content, temp1->content) == 0)
				|| (temp->x == temp1->x && temp->y == temp1->y))
			{
				ft_strdel(line);
				c_destruct(abyss);
				write(1, "ERROR\n", 6);
				exit(-3);
			}
			temp1 = temp1->next;
		}
		temp = temp->next;
	}
}

int			**matrix_init(t_a *abyss)
{
	int		i;

	abyss->matrix = (int **)malloc(sizeof(int *) * abyss->node_count);
	if (abyss->matrix == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (i < abyss->node_count)
	{
		abyss->matrix[i] = ft_intnew(abyss->node_count);
		if (abyss->matrix[i] == NULL)
		{
			while (i != 0)
			{
				i--;
				free(abyss->matrix[i]);
			}
			free(abyss->matrix);
			abyss->matrix = NULL;
			return (NULL);
		}
		i++;
	}
	return (abyss->matrix);
}

char		**names_init(t_a *abyss)
{
	int		i;
	t_lst	*temp;

	if (!(abyss->names = (char **)malloc(sizeof(char *) * abyss->node_count)))
		return (NULL);
	i = 0;
	temp = abyss->head;
	while (i < abyss->node_count)
	{
		abyss->names[i] = ft_strdup(temp->content);
		if (abyss->names[i] == NULL)
		{
			while (i != 0)
			{
				i--;
				free(abyss->names[i]);
			}
			free(abyss->names);
			abyss->names = NULL;
			return (NULL);
		}
		temp = temp->next;
		i++;
	}
	return (abyss->names);
}
