/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lemin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 10:46:41 by jnederlo          #+#    #+#             */
/*   Updated: 2017/08/19 10:44:54 by jnederlo         ###   ########.fr       */
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
	while (get_next_line(0, line))
	{
		if (head == NULL)
			head = node_list(line, map, head);
		node = node_list(line, map, head);
		if (ft_strstr(*line, "##"))
			commands(line, node, map);
		else if (ft_strstr(*line, "#"))
			comments(line, map);
		else if (!ft_strstr(*line, "-"))
			set_nodes(line, node, map);
		else
			break;
	}
	if (!ft_strstr(*line, "-"))
	{
		print_nodes(head);
		return ;
	}
	set_link(line, head, node);
	print_nodes(head);
}

void	set_link(char **line, t_node *head, t_node *node)
{
	char	*node_name;
	char	*link_name;
	t_link	*link;
	t_node	*copy;

	copy = head;
	node_name = ft_word_copy(*line, '-');
	*line += ft_strlen(node_name) + 1;
	link_name = ft_strdup(*line);
	head = traverse_list(head, node_name);
	node = traverse_list(node, link_name);
	head->num_links++;
	link = link_list(head, head->link);
	link->node = node;
	if (head->num_links == 1)
		head->link = link;
	*line -= ft_strlen(node_name) + 1;
	reverse_link(head, node);
	next_link(line, head, node, copy);
}

void	reverse_link(t_node *node, t_node *head)
{
	t_link	*link;

	head->num_links++;
	link = link_list(head, head->link);
	link->node = node;
	if (head->num_links == 1)
		head->link = link;
}

void	next_link(char **line, t_node *head, t_node *node, t_node *copy)
{
	while (get_next_line(0, line))
	{
		head = copy;
		node = copy;
		set_link(line, head, node);
	}
}

t_node	*traverse_list(t_node *node, char *name)
{
	while (ft_strcmp(node->name, name) && node->next != NULL)
		node = node->next;
	return (node);
}

t_link	*link_list(t_node *node, t_link *link)
{
	t_link	*link_node;
	int		num_links;

	num_links = node->num_links;
	if (link == NULL)
	{
		link_node = ft_memalloc(sizeof(t_node));
		link_node->link_num = num_links;
		link_node->next = NULL;
		return (link_node);
	}
	while (num_links != link->link_num && link->next != NULL)
		link = link->next;
	if (num_links == link->link_num)
		return (link);
	link_node = ft_memalloc(sizeof(t_link));
	link_node->link_num = num_links;
	link->next = link_node;
	link_node->next = NULL;
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
	node->link = NULL;
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
	int	num_links;

	while (node)
	{
		num_links = 0;
		ft_printf("node name = %s\n", node->name);
		ft_printf("node coords = (%d, %d)\n", node->x_coord, node->y_coord);
		ft_printf("node is start = %d\n", (int)node->is_start);
		ft_printf("node is end = %d\n", (int)node->is_end);
		while (node->link && num_links < node->num_links)
		{
			ft_printf("link name = %s\n", node->link->node->name);
			node->link = node->link->next;
			num_links++;
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

