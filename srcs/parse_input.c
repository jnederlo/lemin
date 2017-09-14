/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 11:03:56 by jnederlo          #+#    #+#             */
/*   Updated: 2017/09/13 16:11:21 by jnederlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_node	*parse_input(char *line, t_map *map)
{
	t_node	*node;
	t_node	*head;
	// char	*line_copy;

	// line_copy = line;
	head = NULL;
	get_ants(map);
	while (get_next_line(0, &line))
	{
		!head ? head = node_list(line, map, head) : 0;
		node = node_list(line, map, head);
		if (ft_strstr(line, "##"))
			commands(line, node, map);
		else if (ft_strstr(line, "#"))
			comments(line, map);
		else if (!ft_strstr(line, "-"))
			set_nodes(line, node, map);
		else
			break;
	}
	if (!ft_strstr(line, "-"))
		return (NULL);//probably need to do something with this.
	set_link(line, head, node);
	set_distance(map);
	free(line);
	return (head);
}

void	get_ants(t_map *map)
{
	char	*line;

	get_next_line(0, &line);
	map->n_ants = ft_atoi(line);
	ft_printf("%d\n", map->n_ants);
	free(line);
}

void	commands(char *line, t_node *node, t_map *map)
{
	char	*line_copy;

	line_copy = line;
	free(line);
	if (!(ft_strstr(line, "##start") || ft_strstr(line, "##end")))
		return ;
	else if (ft_strstr(line, "start"))
	{
		ft_printf("##start\n");
		get_next_line(0, &line);
		node->is_start = TRUE;
		set_nodes(line, node, map);
	}
	else if (ft_strstr(line, "end"))
	{
		ft_printf("##end\n");
		get_next_line(0, &line);
		node->is_end = TRUE;
		node->is_set = TRUE;
		node->distance = 0;
		set_nodes(line, node, map);
	}
}

void	comments(char *line, t_map *map)
{
	int	len;

	line += 1;
	len = ft_strlen(line);
	map->note = ft_memalloc(sizeof(char) * len + 1);
	map->note = ft_strcpy(map->note, line);
	line -= 1;
	free(line);
	// ft_printf("comment = %s\n\n", map->note);
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
