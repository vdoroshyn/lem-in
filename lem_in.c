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
	ft_putendl(*line);
	ft_strdel(line);
}

int		other_commands(char **line, t_a *abyss)
{
	ft_putendl(*line);
	ft_strdel(line);
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
	ft_putendl(*line);
	ft_strdel(line);
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
		ft_putendl(*line);
		ft_strdel(line);
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
	ft_putendl(*line);
	ft_strdel(line);
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
		ft_putendl(*line);
		ft_strdel(line);
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
			ft_putendl(*line);
			ft_strdel(line);
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
					if (1 + vd_strlen(abyss->names[i]) + vd_strlen(abyss->names[j]) == abyss->len)
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
		ft_putendl(*line);
		ft_strdel(line);
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
				ft_putendl(*line);
				ft_strdel(line);
			}
		}
	}
	else if ((*line)[0] == '#' || link_validate(*line, abyss))
	{
		ft_putendl(*line);
		ft_strdel(line);
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
			ft_putendl(*line);
			ft_strdel(line);
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

void	free_end_start(t_lst **head)
{
	free((*head)->content);
	free(*head);
	*head = NULL;
}

void	free_list(t_a *abyss)
{
	t_lst *temp;

	while (abyss->head != NULL)
	{
		temp = abyss->head->next;
		free(abyss->head->content);
		free(abyss->head);
		abyss->head = temp;
	}
	abyss->head = NULL;
	abyss->start = NULL;
	abyss->end = NULL;
}

t_temp	*create_temp_node(int index)
{
	t_temp *node;

	node = (t_temp *)malloc(sizeof(t_temp));
	if (node == NULL)
	{
		return (node);
	}
	node->room_index = index;
	node->next = NULL;
	return (node);
}

void	free_temp_node(t_a *abyss)
{
	t_temp *tmp;

	if (abyss->test_route != NULL && abyss->test_route->next != NULL)
	{
		tmp = abyss->test_route;
		abyss->test_route = abyss->test_route->next;
		free(tmp);
	}
	else if (abyss->test_route != NULL)
	{
		free(abyss->test_route);
		abyss->test_route = NULL;
	}
}

void	free_temp_list(t_a *abyss)
{
	t_temp *tmp;

	while (abyss->test_route != NULL)
	{
		tmp = abyss->test_route;
		abyss->test_route = abyss->test_route->next;
		free(tmp);
	}
	abyss->test_route = NULL;
}

void	add_to_temp_list(t_a *abyss, int index)
{
	t_temp *node;
	
	node = create_temp_node(index);
	if (node == NULL)
	{
		c_destruct(abyss);
		write(1, "Not enough memory\n", 18);
		exit(-5);
	}
	node->next = abyss->test_route;
	abyss->test_route = node;
}

t_way	*create_way_node(int size)
{
	t_way *node;

	node = (t_way *)malloc(sizeof(t_way));
	if (node == NULL)
	{
		return (node);
	}
	node->size = size;
	node->prev = NULL;
	node->next = NULL;
	node->head = NULL;
	node->tail = NULL;
	return (node);
}

t_route		*new_room(void)
{
	t_route *node;

	node = (t_route *)malloc(sizeof(t_route));
	if (node == NULL)
	{
		return (node);
	}
	node->prev = NULL;
	node->next = NULL;
	node->ant_num = 0;
	return (node);
}

void	new_route_emerges(t_a *abyss, int size)
{
	t_route *tmp1;
	t_temp *tmp2;

	tmp2 = abyss->test_route;
	while (size != 0)
	{
		tmp1 = new_room();
		if (tmp1 == NULL)
		{
			c_destruct(abyss);
			write(1, "Not enough memory\n", 18);
			exit(-5);
		}
		if (abyss->routes->head == NULL)
		{
			tmp1->room_index = tmp2->room_index;
			abyss->routes->tail = tmp1;
			abyss->routes->head = tmp1;
		}
		else
		{
			tmp1->room_index = tmp2->room_index;
			abyss->routes->head->prev = tmp1;
			tmp1->next = abyss->routes->head;
			abyss->routes->head = tmp1;
		}
		tmp2 = tmp2->next;
		size--;
	}
}

void	create_a_route(t_a *abyss, int size)
{
	t_way *node;

	node = create_way_node(size);
	if (node == NULL)
	{
		c_destruct(abyss);
		write(1, "Not enough memory\n", 18);
		exit(-5);
	}
	if (abyss->routes == NULL)
	{
		abyss->routes = node;
	}
	else
	{
		abyss->routes->prev = node;
		node->next = abyss->routes;
		abyss->routes = node;
	}
	new_route_emerges(abyss, size);
}

int		backtracking(t_a *abyss, int index, int *size)
{
	int i;

	*size += 1;
	add_to_temp_list(abyss, index);
	if (index == abyss->node_count - 1)
	{
		create_a_route(abyss, *size);
		//printf("size |%d|\n", *size);
		return (0);
	}
	i = 0;
	while (i < abyss->node_count)
	{	
		if (abyss->matrix[index][i] == 1 && abyss->visit[i] == 0)
		{
			//printf("%d\n", abyss->matrix[index][i]);
			abyss->visit[i] = 1;
			backtracking(abyss, i, size);
			free_temp_node(abyss);
			abyss->visit[i] = 0;
			*size -= 1;
		}
		i++;
	}
	return (1);
}

void	finding_path(t_a *abyss)
{
	int size;

	size = 0;
	abyss->visit = ft_intnew(abyss->node_count);
	if (abyss->visit == NULL)
	{
		c_destruct(abyss);
		write(1, "Not enough memory\n", 18);
		exit(-5);
	}
	for (int i = 0; i < abyss->node_count; i++)
	{
		printf("|%d|", abyss->visit[i]);//TODO
	}
	printf("\n");//TODO
	abyss->visit[0] = 1;
	backtracking(abyss, 0, &size);
	abyss->visit[0] = 0;
	free_temp_node(abyss);
	for (int i = 0; i < abyss->node_count; i++)
	{
		printf("|%d|", abyss->visit[i]);//TODO
	}
	printf("\n");//TODO
}

void	number_nodes(t_a *abyss)
{
	t_way *tmp;
	int i;

	i = 0;
	tmp = abyss->routes;
	while (tmp != NULL)
	{
		tmp->num = i; 
		i++;
		tmp = tmp->next;
	}
}

void	sorting_routes(t_a *abyss)
{
	t_way *temp;
	t_way *inner;
	int flag;
	int swap;

	while (1)
	{
		swap = 0;
		inner = abyss->routes;
		while (inner != NULL && inner->next != NULL)
		{
			flag = 0;
			if (inner->size > inner->next->size)
			{
				swap += 1;
				if (inner->prev == NULL)
				{
					abyss->routes = inner->next;
				}
				if (inner->next->next != NULL)
				{
					inner->next->next->prev = inner;
				}
				temp = inner->next->next;
				inner->next->next = inner->next->prev;
				inner->next->prev = inner->prev;
				if (inner->prev != NULL)
				{
					inner->prev->next = inner->next;
				}
				inner->prev = inner->next;
				inner->next = temp;
				flag = 1;
			}
			if (flag == 0)
			{
				inner = inner->next;
			}
		}
		if (swap == 0)
		{
			break ;
		}
	}
	number_nodes(abyss);
}

int		ft_isunique(t_route *tmp, t_a *abyss)
{
	while (tmp != NULL)
	{
		if (tmp->room_index != 0 && tmp->room_index != abyss->node_count - 1)
		{
			if (abyss->visit[tmp->room_index] == 1)
			{
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

void	rooms_to_visit(t_route *tmp, t_a *abyss)
{
	while (tmp != NULL)
	{
		if (tmp->room_index != 0 && tmp->room_index != abyss->node_count - 1)
		{
			abyss->visit[tmp->room_index] = 1;
		}
		tmp = tmp->next;
	}
}

void	free_best(t_a *abyss)
{
	t_temp *tmp;

	while (abyss->best != NULL)
	{
		tmp = abyss->best;
		abyss->best = abyss->best->next;
		free(tmp);
	}
	abyss->best = NULL;
}

void	route_to_tempset(int num, t_a *abyss)
{
	t_temp *node;

	node = create_temp_node(num);
	if (node == NULL)
	{
		c_destruct(abyss);
		write(1, "Not enough memory\n", 18);
		exit(-6);
	}
	node->next = abyss->test_route;
	abyss->test_route = node;
}

void	visit_to_zero(int *ptr, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		ptr[i] = 0;
		i++;
	}
}

void	set_search(t_way *head, t_a *abyss)
{
	t_way *tmp;
	int num;
	float res;

	while (head != NULL)
	{	
		abyss->len = 0;
		num = 0;
		tmp = head;
		while (tmp != NULL)
		{
			if (ft_isunique(tmp->head, abyss))
			{
				rooms_to_visit(tmp->head, abyss);
				route_to_tempset(tmp->num, abyss);
				num += tmp->size - 1;
				abyss->len += 1;
			}
			tmp = tmp->next;
		}
		res = (float)(abyss->ants + num) / (float)abyss->len;
		if (abyss->priority == 0 || res < abyss->priority)
		{
			abyss->priority = res;
			if (abyss->best != NULL)
			{
				free_best(abyss);
			}
			abyss->best = abyss->test_route;
			abyss->test_route = NULL;
		}
		else
		{
			free_temp_list(abyss); 
		}

		for (int i = 0; i < abyss->node_count; i++)
		{
			printf("|%d|", abyss->visit[i]);//TODO
		}
		printf("\n");//TODO

		visit_to_zero(abyss->visit, abyss->node_count);

		for (int i = 0; i < abyss->node_count; i++)
		{
			printf("|%d|", abyss->visit[i]);//TODO
		}
		printf("\n");//TODO

		// printf("l%d\n", abyss->len);
		// printf("n%d\n", num);
		// printf("r%f\n", res);
		printf("abyss%f\n", abyss->priority);
		head = head->next;
	}
	t_temp *huy = abyss->best;//TODO
	while (huy != NULL)
	{
		printf("%d ", huy->room_index);
		huy = huy->next;
	}
	printf("\n");//TODO
}

void	free_inner(t_route *head)
{	
	t_route *tmp;

	while (head != NULL)
	{
		tmp = head;
		free(tmp);
		head = head->next;
	}
}

void	free_outer(t_way *head, t_a *abyss)
{
	t_way *tmp;

	tmp = head;
	if (head->prev == NULL)
	{
		abyss->routes = head->next;
		if (head->next != NULL)
		{
			head->next->prev = NULL;
		}
	}
	else
	{
		head->prev->next = head->next;
		if (head->next != NULL)
		{
			head->next->prev = head->prev;
		}
	}
	free(tmp);
}

void	destroy_outer(t_a *abyss)
{
	t_way *tmp;
	t_way *tmp1;

	tmp = abyss->routes;
	while (tmp != NULL)
	{
		if (tmp->head != NULL)
		{
			free_inner(tmp->head);
			tmp->head = NULL;
			tmp->tail = NULL;
		}
		tmp1 = tmp;
		free(tmp1);
		tmp = tmp->next;
	}
	abyss->routes = NULL;
}

int		is_in_list(t_temp *best, int num)
{
	while (best != NULL)
	{
		if (best->room_index == num)
		{
			return (1);
		}
		best = best->next;
	}
	return (0);
}

void	remove_odd_routes(t_a *abyss)
{
	t_way *tmp;

	tmp = abyss->routes;
	while (tmp != NULL)
	{
		if (!is_in_list(abyss->best, tmp->num))
		{
			free_inner(tmp->head);
			tmp->head = NULL;
			tmp->tail = NULL;
			free_outer(tmp, abyss);
		}
		tmp = tmp->next;
	}
}

void	its_alive(t_a *abyss)
{
	t_route *tmp;

	tmp = abyss->routes->tail->prev;
	printf("%d\n", tmp->room_index);
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

	its_alive(&abyss);

	c_destruct(&abyss);

	return (0);
}
