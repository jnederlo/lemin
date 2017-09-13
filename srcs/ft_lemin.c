/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lemin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 10:46:41 by jnederlo          #+#    #+#             */
/*   Updated: 2017/09/11 17:57:02 by jnederlo         ###   ########.fr       */
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
	ft_printf("%d\n", map->n_ants);
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
	set_distance(map);
	while (map->n_ants > 0)
	{
		march(map, head, node);
		// head = node;
	}
	// print_nodes(head);
}

void	march(t_map *map, t_node *head, t_node *node)
{
	t_link	*temp;
	int		i;
	int		k;

	k = 0;
	i = 1;
	while (head)
	{
		while (head)
		{
			if (head->was_visited == TRUE)
				head = head->next;
			else
				break ;
		}
		if (head == NULL)
			break ;
		temp = head->link;
		while (temp)
		{
			if (head->num_ants > 0 && temp->node->distance < head->distance &&
				temp->node->was_visited == FALSE && temp->node->is_full == FALSE)
			{
				head->num_ants--;
				head->is_full = FALSE;
				temp->node->num_ants++;
				temp->node->is_full = TRUE;
				temp->node->was_visited = TRUE;
				if (temp->node->is_end == TRUE)
				{
					map->n_ants--;
					temp->node->is_full = FALSE;
				}
				i > 1 ? ft_printf(" ") : 0;
				ft_printf("L%d-%s", i, temp->node->name);
				i++;
			}
			temp = temp->next;
		}
		head = head->next;
		if (head == NULL && k == 0)
		{
			k++;
			head = node;
		}
	}
	reset_node(node);
	ft_printf("\n");
	i = 1;
}

void	reset_node(t_node *node)
{
	t_node	*temp;

	temp = node;
	while (temp)
	{
		temp->was_visited = FALSE;
		temp = temp->next;
	}
}

void	set_distance(t_map *map)
{
	t_node	*current;
	t_queue	*front;
	t_queue	*rear;
	t_link	*temp;

	front = NULL;
	rear = NULL;
	current = map->end;
	temp = current->link;
	while (current)
	{
		temp = current->link;
		while (temp && temp->node)
		{
			if (temp->node->is_set == FALSE)
				enqueue(&front, &rear, temp, current);
			temp = temp->next;
		}
		if (!front)
			return ;
		current = front->node;
		dequeue(&front);
	}
}



void	dequeue(t_queue **front)
{
	t_queue	**temp;

	if (*front != NULL)
	{
		temp = front;
		*front = (*front)->next;
	}
}

void	enqueue(t_queue **front, t_queue **rear, t_link *link, t_node *current)
{
	t_queue *new_node;
	t_node	*node;

	node = link->node;
	new_node = ft_memalloc(sizeof(t_queue));
	new_node->node = node;
	node->distance = current->distance + 1;
	node->is_set = TRUE;
	new_node->next = NULL;
	if (*front == NULL)
	{
		*rear = new_node;
		*front = *rear;
	}
	else
	{
		(*rear)->next = new_node;
		*rear = new_node;
	}
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
	if (!(ft_strstr(*line, "##start") || ft_strstr(*line, "##end")))
		return ;
	else if (ft_strstr(*line, "start"))
	{
		ft_printf("##start\n");
		get_next_line(0, line);
		node->is_start = TRUE;
		set_nodes(line, node, map);
	}
	else if (ft_strstr(*line, "end"))
	{
		ft_printf("##end\n");
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
	// ft_printf("comment = %s\n\n", map->note);
}

