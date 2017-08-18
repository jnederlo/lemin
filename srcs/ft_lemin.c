/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lemin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 10:46:41 by jnederlo          #+#    #+#             */
/*   Updated: 2017/08/17 22:09:45 by jnederlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdio.h>

int		main(int argc, char **argv)
{
	char	*line;

	(void)argc;
	// if (argc != 2)
	// 	return (ft_printf("Error\n"));
	line = argv[1];
	get_ants(&line);
	// print_nodes(head);


	return (0);
}

void	get_ants(char **line)
{
	t_map	*map;

	map = ft_memalloc(sizeof(t_map));
	get_next_line(0, line);
	map->n_ants = ft_atoi(*line);
	ft_printf("# of ants = %d\n\n", map->n_ants);
	get_nodes(line, map);
}

void	get_nodes(char **line, t_map *map)
{
	t_node	*node;
	t_node	*head;

	head = NULL;
	map->node_num = 0;
	map->link_num = 0;
	while (get_next_line(0, line))
	{
		if (head == NULL)
			head = node_list(line, map, head);
		node = node_list(line, map, head);
		if (ft_strstr(*line, "##"))
			commands(line, node, map);
		else if (ft_strstr(*line, "#"))
			comments(line, map);
		else if (ft_strstr(*line, "-"))
			set_links(line, map, head, node);
		else if (*line)
			set_nodes(line, node, map);
	}
	print_nodes(head);
}

void	set_links(char **line, t_map *map, t_node *link, t_node *node)
{
	char	*node_name;
	char	*link_name;
	t_node	*link_head;
	t_node	*head;

	head = link;
	// ft_printf("node->name = %s\n\n", node->name);
	while (get_next_line(0, line))
	{
		link = head;
		node = head;
		// ft_printf("line = %s\n", *line);
		node_name = ft_word_copy(*line, '-');
		*line += ft_strlen(node_name) + 1;
		link_name = ft_strdup(*line);
		while (ft_strcmp(node->name, node_name) && node->next != NULL)
			node = node->next;
		while (ft_strcmp(link->name, link_name) && link->next != NULL)
			link = link->next;
		// if (link_head == NULL)
			link_head = link;
		node->next_link = link_list(map, link_head);
		// ft_printf("link_node->name = %s\n", link_node->name);
		// ft_printf("node_name = %s\n", node_name);
		// ft_printf("link_name = %s\n", link_name);
		// ft_printf("node->name = %s\n", node->name);
		// ft_printf("link->name = %s\n\n", link->name);
		map->link_num++;
		*line -= ft_strlen(node_name) + 1;
	}
}

t_node	*link_list(t_map *map, t_node *link_head)
{
	t_node	*link_node;
	int		link_num;

	link_num = map->link_num;
	while (link_num != link_head->link_num && link_head->next_link != NULL)
		link_head = link_head->next_link;
	if (link_num == link_head->link_num)
		return (link_head);
	link_node = link_head;//maybe problem
	link_node->link_num = link_num;
	link_head->next_link = link_node;
	link_node->next_link = NULL;
	return (link_node);
}

t_node	*node_list(char **line, t_map *map, t_node *head)
{
	t_node	*node;
	int		node_num;

	if (ft_strstr(*line, "-"))
		return (head);
	node_num = map->node_num;
	if (head == NULL)
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

void	set_nodes(char **line, t_node *node, t_map *map)
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
	node->next_link = NULL;
	*line -= name_len + count;
	map->node_num++;
}

void	clear_node(t_map *map)
{
	map->node->x_coord = -1;
	map->node->y_coord = -1;
	map->node->is_full = FALSE;
	map->node->is_start = FALSE;
	map->node->is_end = FALSE;
}

void	print_nodes(t_node *node)
{
	while (node)
	{
		ft_printf("node name = %s\n", node->name);
		ft_printf("node coords = (%d, %d)\n", node->x_coord, node->y_coord);
		ft_printf("node is start = %d\n", (int)node->is_start);
		ft_printf("node is end = %d\n", (int)node->is_end);
		while (node->next_link)
		{
			printf("link name = %s\n", node->next_link->name);
			node->next_link = node->next_link->next_link;
		}
		ft_printf("\n");
		node = node->next;
	}
}

void	commands(char **line, t_node *node, t_map *map)
{
	// map->node = ft_memalloc(sizeof(t_node));
	if (!(ft_strstr(*line, "##start") || ft_strstr(*line, "##end")))
		return ;
	else if (ft_strstr(*line, "start"))
	{
		get_next_line(0, line);
		node->is_start = TRUE;
		set_nodes(line, node, map);
	}
	else if (ft_strstr(*line, "end"))
	{
		get_next_line(0, line);
		node->is_end = TRUE;
		set_nodes(line, node, map);
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

