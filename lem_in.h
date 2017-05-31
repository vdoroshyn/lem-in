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

//ants validation
void	ft_read_ants(char **line, t_a *abyss);

//destruct
void	destroy_outer(t_a *abyss);
void	free_best(t_a *abyss);
void	free_list(t_a *abyss);
void	free_end_start(t_lst **head);
void	free_temp_list(t_a *abyss);
void	c_destruct(t_a *abyss);
#endif
