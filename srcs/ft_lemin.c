/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lemin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 10:46:41 by jnederlo          #+#    #+#             */
/*   Updated: 2017/08/19 22:09:04 by jnederlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdio.h>

int		main(int argc, char **argv)
{
	char	*line;
	t_map	*map;

	map = ft_memalloc(sizeof(t_map));
	(void)argc;
	// if (argc != 2)
	// 	return (ft_printf("Error\n"));
	line = argv[1];
	parse_input(&line, map);
	// print_nodes(head);


	return (0);
}

void	get_ants(char **line, t_map *map)
{
	get_next_line(0, line);
	map->n_ants = ft_atoi(*line);
	ft_printf("# of ants = %d\n\n", map->n_ants);
}

void	parse_input(char **line, t_map *map)
{
	t_node	*node;
	t_node	*head;

	head = NULL;
	get_ants(line, map);
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
	// set_distance(map->end, map);
	set_distance(map);
	print_nodes(head);
}

// void	set_distance(t_node *node, t_map *map)
// {

// 	if (node->is_start)
// 	while ()


// }


















// void	set_queue(t_map *map)
// {
// 	t_queue	*q_head;
// 	t_queue	*q_tail;
// 	t_link	*fuck;
// 	int distance;
	
// 	distance = 1;
// 	fuck = map->end->link;
// 	q_head = NULL;
// 	q_tail = NULL;
// 	while (fuck)
// 	{
// 		enqueue(fuck->node, &q_head, &q_tail);
// 		if (!q_tail->node->is_set)
// 		{
// 			q_tail->node->distance = distance;
// 			q_tail->node->is_set = TRUE;
// 		}
// 		// new_queue(q_tail->node);
// 		distance++;
// 		fuck = fuck->node->link;
// 	}
// }

void	set_distance(t_map *map)
{
	t_queue	*q_head;
	t_queue *q_distance;
	t_queue	*p;
	int distance;

	distance = 0;
	q_head = ft_memalloc(sizeof(t_queue));
	q_head->node = map->end;
	q_head->next = NULL;
	q_head->node->distance = distance;
	distance++;
	q_distance = q_head;
	while (q_distance != NULL)
	{
		q_distance = depth(q_head);
		p = q_distance;
		while (p != NULL)
		{
			p->node->distance = distance;
			p = p->next;
		}
		q_head = q_distance;
		distance++;
	}
}

t_queue	*depth(t_queue *head)
{
	// need to iterate through the head queue, get each child,
	//  and add each one to depth queue
	t_queue	*depth;
	t_queue	*q_head;
	t_link	*parent;
	t_node	*node;

	depth = NULL;
	q_head = NULL;
	while (head != NULL)
	{
		parent = head->node->link;
		if (depth == NULL)
		{
			depth = ft_memalloc(sizeof(t_queue));
			depth->node = get_next_child(parent);
			if (depth->node == NULL)
				return (NULL);
			depth->next = NULL;
			q_head = depth;
		}
		while ((node = get_next_child(parent)))
		{	
			depth->next = ft_memalloc(sizeof(t_queue));
			depth = depth->next;
			depth->node = node;
			depth->next = NULL;
		}
		head = head->next;
	}
	return (q_head);
}

t_node *get_next_child(t_link *parent)
{
	while (parent != NULL)
	{
		if (parent->node->is_set == FALSE)
		{
			parent->node->is_set = TRUE;
			return (parent->node);
		}
		parent = parent->next;
	}
	return (NULL);
}

// void	new_queue(t_node *node)
// {
// 	t_queue	*q_head;
// 	t_queue	*q_tail;

// 	q_head = NULL;
// 	q_tail = NULL;
// 	while (node->link->node)
// 	{
// 		enqueue(node->link->node, &q_head, &q_tail);
// 		if (!q_tail->node->is_end && !q_tail->node->is_set)
// 		{
// 			q_tail->node->distance = node->distance + 1;
// 			q_tail->node->is_set = TRUE;
// 		}
// 		node->link->node = node->link->next->node;
// 	}
// }


// void	enqueue(t_node *node, t_queue **q_head, t_queue **q_tail)
// {
// 	t_queue	*temp;

// 	temp = ft_memalloc(sizeof(t_queue));
// 	temp->node = node;
// 	temp->next = NULL;
// 	if (*q_head == NULL && *q_tail == NULL)
// 	{
// 		*q_head = temp;
// 		*q_tail = temp;
// 		return ;
// 	}
// 	(*q_tail)->next = temp;
// 	*q_tail = temp;
// }

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
		ft_printf("node distance = %d\n", node->distance);
		ft_printf("is set = %d\n", (int)node->is_set);
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
		node->is_set = TRUE;
		node->distance = 0;
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

