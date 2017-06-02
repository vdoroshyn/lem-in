/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 17:20:42 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/04/20 17:20:47 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	c_destruct(t_a *abyss)
{
	if (abyss->matrix != NULL)
	{
		free_2d_array((void **)abyss->matrix, abyss->node_count);
		abyss->matrix = NULL;
	}
	if (abyss->names != NULL)
	{
		free_2d_array((void **)abyss->names, abyss->node_count);
		abyss->names = NULL;
	}
	if (abyss->head != NULL)
	{
		free_list(abyss);
	}
	if (abyss->end != NULL)
	{
		free_end_start(&abyss->end);
	}
	if (abyss->start != NULL)
	{
		free_end_start(&abyss->start);
	}
	if (abyss->visit != NULL)
	{
		free(abyss->visit);
		abyss->visit = NULL;
	}
	if (abyss->test_route != NULL)
	{
		free_temp_list(abyss);
	}
	if (abyss->best != NULL)
	{
		free_best(abyss);
	}
	if (abyss->routes != NULL)
	{
		destroy_outer(abyss);
	}
}

int		ft_coords_atoi(const char *str)
{
	int res;
	int i;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > 214748364 || (res == 214748364 && str[i] > '7'))
		{
			return (-1);
		}
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

void	coords_to_node(char **line, int *x, int *y, t_a *abyss)
{
	int i;

	i = 0;
	while ((*line)[i] != ' ')
	{
		i++;
	}
	i++;
	*x = ft_coords_atoi(&(*line)[i]);
	if (*x == -1)
	{
		ft_strdel(line);
		c_destruct(abyss);
		write(1, "ERROR\n", 6);
		exit(-2);
	}
	while ((*line)[i] != ' ')
	{
		i++;
	}
	i++;
	*y = ft_coords_atoi(&(*line)[i]);
	if (*y == -1)
	{
		ft_strdel(line);
		c_destruct(abyss);
		write(1, "ERROR\n", 6);
		exit(-2);
	}
}

int		search_for_two_spaces(char *line)
{
	int i;
	int space;

	i = 0;
	space = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
		{
			space++;
		}
		i++;
	}
	if (space == 2)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int		room_validate(char *line)
{
	int i;
	int flag;

	if (line[0] == '#' || line[0] == '\0' || line[0] == 'L' || !search_for_two_spaces(line))
	{
		return (0);
	}
	i = 0;
	while (line[i] != ' ')
	{
		if (!ft_isprint_nospace(line[i]))
		{
			return (0);
		}
		i++;
	}
	i++;
	while (line[i] != ' ')
	{
		if (!ft_isdigit(line[i]))
		{
			return (0);
		}
		i++;
	}
	i++;
	flag = 0;
	while (line[i] != '\0')
	{
		if (!ft_isdigit(line[i]))
		{
			return (0);
		}
		i++;
		flag++;
	}
	if (flag == 0)
	{
		return (0);
	}
	return (1);
}

void	room_to_list(char **line, t_a *abyss)
{
	t_lst *temp;

	temp = (t_lst *)malloc(sizeof(t_lst));
	if (temp == NULL)
	{
		ft_strdel(line);
		c_destruct(abyss);
		write(1, "Not enough memory\n", 18);
		exit(-2);
	}
	temp->content = ft_strdup_space(*line);
	if (temp->content == NULL)
	{
		ft_strdel(line);
		free(temp);
		c_destruct(abyss);
		write(1, "Not enough memory\n", 18);
		exit(-2);
	}
	coords_to_node(line, &temp->x, &temp->y, abyss);
	temp->next = abyss->head;
	abyss->head = temp;
	abyss->node_count += 1;
	ft_putendlstrdel(line);
}

int		other_commands(char **line, t_a *abyss)
{
	ft_putendlstrdel(line);
	get_next_line(0, line);
	if (*line != NULL && room_validate(*line))
	{
		room_to_list(line, abyss);
		ft_strdel(line);
		return (0);
	}
	else if (*line == NULL)
	{
		c_destruct(abyss);
		write(1, "ERROR\n", 6);
		exit(-2);
	}
	else
	{
		return (1);
	}
}

void	check_start(char **line, t_a *abyss)
{
	if (abyss->start != NULL)
	{
		ft_strdel(line);
		c_destruct(abyss);
		write(1, "ERROR\n", 6);
		exit(-2);
	}
	ft_putendlstrdel(line);
	get_next_line(0, line);
	if (*line != NULL && room_validate(*line))
	{
		abyss->start = (t_lst *)malloc(sizeof(t_lst));
		if (abyss->start == NULL)
		{
			ft_strdel(line);
			c_destruct(abyss);
			write(1, "Not enough memory\n", 18);
			exit(-2);
		}
		abyss->start->content = ft_strdup_space(*line);
		if (abyss->start->content == NULL)
		{
			ft_strdel(line);
			free(abyss->start);
			abyss->start = NULL;
			c_destruct(abyss);
			write(1, "Not enough memory\n", 18);
			exit(-2);
		}
		coords_to_node(line, &abyss->start->x, &abyss->start->y, abyss);
		abyss->start->next = NULL;
		ft_putendlstrdel(line);
	}
	else
	{
		ft_strdel(line);
		c_destruct(abyss);
		write(1, "ERROR\n", 6);
		exit(-2);
	}
}	

void	check_end(char **line, t_a *abyss)
{
	if (abyss->end != NULL)
	{
		ft_strdel(line);
		c_destruct(abyss);
		write(1, "ERROR\n", 6);
		exit(-2);
	}
	ft_putendlstrdel(line);
	get_next_line(0, line);
	if (*line != NULL && room_validate(*line))
	{
		abyss->end = (t_lst *)malloc(sizeof(t_lst));
		if (abyss->end == NULL)
		{
			ft_strdel(line);
			c_destruct(abyss);
			write(1, "Not enough memory\n", 18);
			exit(-2);
		}
		abyss->end->content = ft_strdup_space(*line);
		if (abyss->end->content == NULL)
		{
			ft_strdel(line);
			free(abyss->end);
			abyss->end = NULL;
			c_destruct(abyss);
			write(1, "Not enough memory\n", 18);
			exit(-2);
		}
		coords_to_node(line, &abyss->end->x, &abyss->end->y, abyss);
		abyss->end->next = NULL;
		ft_putendlstrdel(line);
	}
	else
	{
		ft_strdel(line);
		c_destruct(abyss);
		write(1, "ERROR\n", 6);
		exit(-2);
	}
}

int		ft_read_rooms(char **line, t_a *abyss)
{
	while (get_next_line(0, line) > 0)
	{
		if (ft_strcmp(*line, "##start") == 0)
		{
			check_start(line, abyss);
		}
		else if (ft_strcmp(*line, "##end") == 0)
		{
			check_end(line, abyss);
		}
		else if (vd_strlen(*line) > 3 && (*line)[0] == '#' && (*line)[1] == '#')
		{
			if (other_commands(line, abyss))
			{
				return (2);
			}
		}
		else if ((*line)[0] == '#')
		{
			ft_putendlstrdel(line);
		}
		else if (room_validate(*line))
		{
			room_to_list(line, abyss);
		}
		else
		{
			if (abyss->start == NULL || abyss->end == NULL)
			{
				ft_strdel(line);
				c_destruct(abyss);
				write(1, "ERROR\n", 6);
				exit(-2);
			}
			return (1);
		}
	}
	return (0);
}

void	start_end_to_list(t_a *abyss)
{
	t_lst *temp;
	
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

void	validate_room_names_coords(t_a *abyss, char **line)
{
	t_lst *temp;
	t_lst *temp1;

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
				c_destruct(abyss);//only abyss->head
				write(1, "ERROR\n", 6);
				exit(-3);
			}
			// printf(  "temp content: |%s|, x: |%d|, y: |%d|\n", temp->content, temp->x, temp->y);
			// printf("temp 1 content: |%s|, x: |%d|, y: |%d|\n", temp1->content, temp1->x, temp1->y);
			temp1 = temp1->next;
		}
		// printf("\n");
		temp = temp->next;
	}
}

int		**matrix_init(t_a *abyss)
{
	int i;

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

char	**names_init(t_a *abyss)
{
	int i;
	t_lst *temp;

	abyss->names = (char **)malloc(sizeof(char *) * abyss->node_count);
	if (abyss->names == NULL)
	{
		return (NULL);
	}
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

int		ft_hyphen(char *line)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '-')
		{
			len += 1;
		}
		i++;
	}
	if (len == 1)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int		link_validate(char *line, t_a *abyss)
{
	int i;
	int j;

	if (!ft_hyphen(line))
	{
		return (0);
	}
	i = 0;
	abyss->len = vd_strlen(line);
	while (i < abyss->node_count)
	{
		if (ft_strstr(line, abyss->names[i]))
		{
			j = i + 1;
			while (j < abyss->node_count)
			{
				if (ft_strstr(line, abyss->names[j]))
				{
					if ((1 + vd_strlen(abyss->names[i]) + vd_strlen(abyss->names[j])) == abyss->len)
					{

						if (abyss->matrix[i][j] == 0 && abyss->matrix[j][i] == 0)
						{
							abyss->matrix[i][j] = 1;
							abyss->matrix[j][i] = 1;
							return (1);
						}
					}
				}
				j++;
			}
		}
		i++;
	}
	return (0);
}

int		ft_check_links(char **line, t_a *abyss)
{
	if ((ft_strcmp("##start", *line) == 0) || (ft_strcmp("##end", *line) == 0))
	{
		ft_strdel(line);
		c_destruct(abyss);
		write(1, "ERROR\n", 6);
		exit(-4);
	}
	else if (vd_strlen(*line) > 3 && (*line)[0] == '#' && (*line)[1] == '#')
	{
		ft_putendlstrdel(line);
		if (get_next_line(0, line) > 0)
		{
			if (!(link_validate(*line, abyss)))
			{
				ft_strdel(line);
				c_destruct(abyss);
				write(1, "ERROR\n", 6);
				exit(-4);
			}
			else
			{
				ft_putendlstrdel(line);
			}
		}
	}
	else if ((*line)[0] == '#' || link_validate(*line, abyss))
	{
		ft_putendlstrdel(line);
	}
	else
	{
		return (0);
	}
	return (1);
}

int		ft_read_links(char **line, t_a *abyss)
{
	if (abyss->flag == 2)
	{
		if (!(link_validate(*line, abyss)))
		{
			ft_strdel(line);
			c_destruct(abyss);
			write(1, "ERROR\n", 6);
			exit(-4);
		}
		else
		{
			ft_putendlstrdel(line);
		}
	}
	else if (!ft_check_links(line, abyss))
	{
		return (0);
	}
	while (get_next_line(0, line) > 0)
	{
		if (!ft_check_links(line, abyss))
		{
			return (0);
		}
	}
	return (1);
}

int		main(void)
{
	char *line;
	t_a abyss;

	abyss.head = NULL;
	abyss.start = NULL;
	abyss.end = NULL;
	abyss.ants = 0;
	abyss.node_count = 2;
	line = NULL;
	abyss.flag = 0;
	abyss.routes = NULL;
	abyss.test_route = NULL;
	abyss.visit = NULL;
	abyss.best = NULL;
	abyss.priority = 0;
	abyss.matrix = NULL;
	abyss.names = NULL;
	ft_read_ants(&line, &abyss);
	if (!(abyss.flag = ft_read_rooms(&line, &abyss)))
	{
		c_destruct(&abyss);
		write(1, "ERROR\n", 6);
		exit(-2);
	}
	start_end_to_list(&abyss);
	validate_room_names_coords(&abyss, &line);
	if (!matrix_init(&abyss))
	{
		c_destruct(&abyss);
		write(1, "Not enough memory\n", 18);
		exit(-3);
	}
	if (!names_init(&abyss))
	{
		c_destruct(&abyss);
		write(1, "Not enough memory\n", 18);
		exit(-3);
	}
	if (!ft_read_links(&line, &abyss))
	{
		ft_strdel(&line);
		c_destruct(&abyss);
		write(1, "ERROR\n", 6);
		exit(-4);
	}

	for (int i = 0; i < abyss.node_count; i++)
	{
		for (int j = 0; j < abyss.node_count; j++)
		{
			printf(" %d ", abyss.matrix[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < abyss.node_count; i++)
	{
		printf("|%s|\n", abyss.names[i]);
	}
	
	finding_path(&abyss);
	if (abyss.routes == NULL)
	{
		write(1, "ERROR\n", 6);
		exit(-4);
	}


	t_way *lal = abyss.routes;
	t_route *huy;
	while (lal != NULL)
	{
		huy = lal->head;
		while (huy != NULL)
		{
			printf("|%d| - ", huy->room_index);
			huy = huy->next;
		}
		printf("\n");
		lal = lal->next;
	}
	printf("\n");
	sorting_routes(&abyss);

	lal = abyss.routes;
	while (lal != NULL)
	{
		huy = lal->head;
		while (huy != NULL)
		{
			printf("|%d| - ", huy->room_index);
			huy = huy->next;
		}
		printf("\n");
		lal = lal->next;
	}

	set_search(abyss.routes, &abyss);
	remove_odd_routes(&abyss);

	lal = abyss.routes;
	while (lal != NULL)
	{
		huy = lal->head;
		while (huy != NULL)
		{
			printf("|%d| - ", huy->room_index);
			huy = huy->next;
		}
		printf("\n");
		lal = lal->next;
	}

	moving_ants(&abyss);

	c_destruct(&abyss);

	return (0);
}
