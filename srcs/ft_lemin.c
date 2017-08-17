/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lemin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 10:46:41 by jnederlo          #+#    #+#             */
/*   Updated: 2017/08/16 19:22:10 by jnederlo         ###   ########.fr       */
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
	t_node	*head;
	t_node	*node;

	map = ft_memalloc(sizeof(t_map));
	get_next_line(0, line);
	map->n_ants = ft_atoi(*line);
	ft_printf("# of ants = %d\n\n", map->n_ants);
	map->node_num = 0;
	while (get_next_line(0, line))
	{
		if (map->node_num == 0)
			head = node_list(map, head, 1);
		node = node_list(map, head, 0);
		// clear_node(map);
		if (ft_strstr(*line, "##"))
			commands(line, node);
		else if (ft_strstr(*line, "#"))
		{
			map->node_num--;
			comments(line, map);
		}
		else if (ft_strstr(*line, "-"))
			links(line, node);
		else
			rooms(line, node);
		map->node_num++;
	}
	while (head)
	{
		print_node(head);
		head = head->next;
	}
}

t_node	*node_list(t_map *map, t_node *head, int status)
{
	t_node	*node;
	int		node_num;

	node_num = map->node_num;
	if (node_num == 0 && status)
	{
		node = ft_memalloc(sizeof(t_node));
		node->node_num = node_num;
		node->next = NULL;
		return (node);
	}
	while (node_num != head->node_num && head->next != NULL)
		head = head->next;
	if (node_num == head->node_num)
		return (head);
	node = ft_memalloc(sizeof(t_node));
	node->node_num = node_num;
	head->next = node;
	node->next = NULL;
	return (node);
}

void	rooms(char **line, t_node *node)
{
	int		name_len;
	char	*name;
	int		count;

	name = ft_word_copy(*line, ' ');
	name_len = ft_strlen(name) + 1;
	node->name = ft_memalloc(sizeof(char) * name_len);
	node->name = name;
	*line += name_len;
	node->x_coord = ft_atoi(*line);
	count = ft_count_digits(node->x_coord) + 1;
	*line += count;
	node->y_coord = ft_atoi(*line);
	count += ft_count_digits(node->y_coord);
	*line -= name_len + count;
}

void	links(char **line, t_node *node)
{
	(void)**line;
	(void)*node;
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

void	print_node(t_node *node)
{
	ft_printf("node name = %s\n", node->name);
	ft_printf("node coords = (%d, %d)\n", node->x_coord, node->y_coord);
	ft_printf("node is start = %d\n", (int)node->is_start);
	ft_printf("node is end = %d\n\n", (int)node->is_end);
}

void	commands(char **line, t_node *node)
{
	// map->node = ft_memalloc(sizeof(t_node));
	if (!(ft_strstr(*line, "##start") || ft_strstr(*line, "##end")))
		return ;
	else if (ft_strstr(*line, "start"))
	{
		get_next_line(0, line);
		node->is_start = TRUE;
		rooms(line, node);
	}
	else if (ft_strstr(*line, "end"))
	{
		get_next_line(0, line);
		node->is_end = TRUE;
		rooms(line, node);
	}
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

