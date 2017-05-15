/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 13:36:42 by vdoroshy          #+#    #+#             */
/*   Updated: 2016/12/09 11:57:51 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*delim_strdup(char const *s, char c)
{
	int			i;
	int			word_len;
	char		*ptr;

	word_len = 0;
	while (s[word_len] != c && s[word_len] != '\0')
	{
		word_len++;
	}
	if ((ptr = ft_strnew(word_len)) == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (word_len != 0)
	{
		ptr[i] = *s;
		i++;
		s++;
		word_len--;
	}
	return (ptr);
}

static int		word_counter(char const *s, char c)
{
	int			i;
	int			word_counter;

	word_counter = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
		{
			i++;
		}
		if (s[i] != c && s[i] != '\0')
		{
			word_counter++;
		}
		while (s[i] != c && s[i] != '\0')
		{
			i++;
		}
	}
	return (word_counter);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**ptr;
	int			i;
	int			j;
	int			size;

	if (s == NULL)
		return (NULL);
	size = word_counter(s, c);
	ptr = (char **)malloc(sizeof(char *) * (size + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (j < size)
	{
		while (s[i] == c)
			i++;
		ptr[j] = delim_strdup(&s[i], c);
		while (s[i] != c && s[i] != '\0')
			i++;
		j++;
	}
	ptr[j] = NULL;
	return (ptr);
}
