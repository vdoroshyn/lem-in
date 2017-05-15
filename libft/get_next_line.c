/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 14:56:09 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/03/03 14:47:44 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_r(char *line, size_t size, ssize_t add_size)
{
	char		*ptr;

	ptr = NULL;
	if (size == 0)
	{
		ptr = ft_strnew(add_size);
	}
	else
	{
		if (!(ptr = ft_strnew(size + add_size)))
		{
			return (ptr);
		}
		ft_strcpy(ptr, line);
		free(line);
	}
	return (ptr);
}

static int		ft_insert(char *line, char *buf)
{
	size_t		i;
	size_t		j;

	i = ft_strlen(line);
	j = 0;
	while (buf[j] != '\0')
	{
		if (buf[j] == '\n')
		{
			line[i] = '\0';
			j++;
			ft_strcpy(buf, &buf[j]);
			return (1);
		}
		else
		{
			line[i++] = buf[j++];
		}
	}
	ft_bzero(buf, BUFF_SIZE + 1);
	return (0);
}

static int		ft_norme(ssize_t scanned, ssize_t count)
{
	if (scanned == -1)
	{
		return (-1);
	}
	else
	{
		if (count > 0)
		{
			return (1);
		}
		else
		{
			return (0);
		}
	}
}

int				get_next_line(const int fd, char **line)
{
	static char	lft[BUFF_SIZE + 1];
	ssize_t		size[3];

	size[1] = 0;
	size[2] = 0;
	if (line == NULL || fd < 0)
		return (-1);
	while (1)
	{
		if (*lft != '\0')
			size[0] = ft_strlen(lft);
		else
		{
			size[0] = read(fd, lft, BUFF_SIZE);
			if (size[0] == 0 || size[0] == -1)
				return (ft_norme(size[0], size[1]));
			lft[size[0]] = '\0';
		}
		if (!(*line = ft_r(*line, size[2], size[0])))
			return (-1);
		size[2] += size[0];
		if (ft_insert(*line, lft))
			return (!(*line = ft_r(*line, ft_strlen(*line), 0)) ? (-1) : (1));
		size[1] = ft_strlen(*line);
	}
}
