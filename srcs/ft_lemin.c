/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lemin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 10:46:41 by jnederlo          #+#    #+#             */
/*   Updated: 2017/08/16 14:42:49 by jnederlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		main(int argc, char **argv)
{
	char	*line;

	(void)argc;
	// if (argc != 2)
	// 	return (ft_printf("Error\n"));
	line = argv[1];
	setup_map(&line);


	return (0);
}

void	setup_map(char **line)
{
	t_map	*map;

	map = ft_memalloc(sizeof(t_map));
	get_next_line(0, line);
	map->n_ants = ft_atoi(*line);
	ft_printf("# of ants = %d\n\n", map->n_ants);
	while (get_next_line(0, line))
	{
		map->node = ft_memalloc(sizeof(t_node));
		clear_node(map);
		if (ft_strstr(*line, "##"))
			commands(line, map);
		else if (ft_strstr(*line, "#"))
			comments(line, map);
		else if (ft_strstr(*line, "-"))
			links(line, map);
		else
			rooms(line, map);
	}
}

void	links(char **line, t_map *map)
{
	(void)**line;
	(void)*map;
	return ;
}

void	clear_node(t_map *map)
{

	map->node->x_coord = -1;
	map->node->y_coord = -1;
	map->node->is_full = FALSE;
	map->node->is_start = FALSE;
	map->node->is_end = FALSE;
}

void	print_node(t_map *map)
{
	ft_printf("node name = %s\n", map->node->name);
	ft_printf("node coords = (%d, %d)\n", map->node->x_coord, map->node->y_coord);
	ft_printf("node is start = %d\n", (int)map->node->is_start);
	ft_printf("node is end = %d\n\n", (int)map->node->is_end);
}

void	commands(char **line, t_map *map)
{
	// map->node = ft_memalloc(sizeof(t_node));
	if (!(ft_strstr(*line, "##start") || ft_strstr(*line, "##end")))
		return ;
	else if (ft_strstr(*line, "start"))
	{
		get_next_line(0, line);
		map->node->is_start = TRUE;
		rooms(line, map);
	}
	else if (ft_strstr(*line, "end"))
	{
		get_next_line(0, line);
		map->node->is_end = TRUE;
		rooms(line, map);
	}

}

void	rooms(char **line, t_map *map)
{
	int		name_len;
	char	*name;
	int		count;

	name = ft_word_copy(*line, ' ');
	name_len = ft_strlen(name) + 1;
	map->node->name = ft_memalloc(sizeof(char) * name_len);
	map->node->name = name;
	*line += name_len;
	map->node->x_coord = ft_atoi(*line);
	count = ft_count_digits(map->node->x_coord) + 1;
	*line += count;
	map->node->y_coord = ft_atoi(*line);
	count += ft_count_digits(map->node->y_coord);
	line -= name_len + count;
	print_node(map);
}

void	comments(char **line, t_map *map)
{
	int	len;

	*line += 1;
	len = ft_strlen(*line);
	map->note = ft_memalloc(sizeof(char) * len + 1);
	map->note = ft_strcpy(map->note, *line);
	ft_printf("comment = %s\n\n", map->note);
}

