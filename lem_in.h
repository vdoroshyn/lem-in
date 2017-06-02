/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 17:20:54 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/04/20 17:20:59 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# include <stdio.h>

typedef struct		s_lst
{
	char			*content;
	int 			x;
	int 			y;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_temp
{
	int				room_index;
	struct s_temp	*next;
}					t_temp;

typedef struct		s_route
{
	struct s_route	*prev;
	struct s_route	*next;
	int				ant_num;
	int				room_index;
}					t_route;

typedef struct		s_ways
{
	t_route			*head;
	t_route			*tail;
	int				size;
	int				num;
	int				stop;
	struct s_ways	*prev;
	struct s_ways	*next;
}					t_way;

typedef struct		s_ants
{
	int ants;
	int len;
	int node_count;
	int flag;
	float priority;
	int **matrix;
	char **names;
	int *visit;
	t_way *routes;
	t_temp *test_route;
	t_temp *best;
	t_lst *head;
	t_lst *start;
	t_lst *end;
}	t_a;

//augumented libft functions
int		ft_strlen_space(const char *s);
char	*ft_strdup_space(const char *s1);
int		ft_isprint_nospace(char c);
int		vd_strlen(const char *s);

void	ft_putendlstrdel(char **line);
//ants validation
void	ft_read_ants(char **line, t_a *abyss);
int		ft_ants_atoi(const char *str);
//moving ants
void	moving_ants(t_a *abyss);
void	add_route_priority(t_way *head);
//sorting routes
void			sorting_routes(t_a *abyss);
//set_search
void	set_search(t_way *head, t_a *abyss);
void		route_to_tempset(int num, t_a *abyss);
//creating and adding
t_route		*new_room(void);
t_way	*create_way_node(int size);
t_temp	*create_temp_node(int index);
void	add_to_temp_list(t_a *abyss, int index);
void	new_route_emerges(t_a *abyss, int size);
void		create_a_route(t_a *abyss, int size);
//finding path
void	finding_path(t_a *abyss);
//destruct
void	remove_odd_routes(t_a *abyss);
void	destroy_outer(t_a *abyss);
void	free_inner(t_route *head);

void	free_best(t_a *abyss);
void	free_list(t_a *abyss);
void	free_end_start(t_lst **head);
void	free_temp_node(t_a *abyss);
void	free_temp_list(t_a *abyss);
void	c_destruct(t_a *abyss);
#endif
