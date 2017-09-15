/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_copy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 20:04:52 by jnederlo          #+#    #+#             */
/*   Updated: 2017/09/14 15:48:56 by jnederlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Counts how many elements in a word.
** Creates the appropriate amount of space for the word (with ft_strnew).
** Creates a copy of the word into a new array pointed to by start.
** Returns start.
*/

#include "../includes/libft.h"

char	*ft_word_copy(char *s, char c)
{
	int		j;
	char	*start;

	j = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s != c && *s)
			start = s;
		while (*s != c && *s)
		{
			s++;
			j++;
		}
		start = ft_strnew(j);
		start = ft_strncpy(start, s - j, j);
		return (start);
	}
	return (0);
}
