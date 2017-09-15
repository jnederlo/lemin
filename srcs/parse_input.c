/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 11:03:56 by jnederlo          #+#    #+#             */
/*   Updated: 2017/09/15 15:24:53 by jnederlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_node	*parse_input(t_map *map)
{
	t_node	*node;
	t_node	*head;
	char	*line;

	head = NULL;
	get_ants(map);
	while (get_next_line(0, &line) > 0)
	{
		!head ? head = node_list(line, map, head) : 0;
		node = node_list(line, map, head);
		if (ft_strstr(line, "##"))
			commands(line, node, map);
		else if (ft_strstr(line, "#"))
			ft_printf("%s\n", line);
		else if (!ft_strstr(line, "-"))
			set_nodes(line, node, map);
		else
			set_link(line, head, node);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	set_distance(map);
	return (head);
}

void	get_ants(t_map *map)
{
	char	*line;

	//add error check here for no ants or not a number.
	get_next_line(0, &line);
	map->n_ants = ft_atoi(line);
	ft_printf("%d\n", map->n_ants);
	ft_strdel(&line);
}

int		commands(char *line)
{
	if (!(ft_strcmp(line, "##start") || ft_strcmp(line, "##end")))
	{
		// ft_strdel(&line);
		ft_printf("ERROR\n");
		return (-1);
	}
	ft_printf("%s\n" line);
	if (ft_strcmp(line, "start"))
		return (1);
	else
		return (2);
}


void	commands(char *line, t_node *node, t_map *map)
{
	char	*line_copy;

	line_copy = ft_strdup(line);
	// ft_strdel(&line);
	if (!(ft_strstr(line_copy, "##start") || ft_strstr(line_copy, "##end")))
	{
		ft_strdel(&line_copy);
		ft_printf("ERROR\n");
		return ;
	}
	if (ft_strstr(line_copy, "start"))
	{
		ft_printf("##start\n");
		get_next_line(0, &line_copy);
		node->is_start = TRUE;
		set_nodes(line_copy, node, map);
	}
	else if (ft_strstr(line_copy, "end"))
	{
		ft_printf("##end\n");
		get_next_line(0, &line_copy);
		node->is_end = TRUE;
		node->is_set = TRUE;
		node->distance = 0;
		set_nodes(line_copy, node, map);
	}
	ft_strdel(&line_copy);
}

// void	comments(char *line)
// {
// 	// (void)map;
// 	// int	len;
// 	// int	i;

// 	// i = 1;
// 	// len = ft_strlen(&line[i]) + 1;
// 	// map->note = ft_memalloc(sizeof(char) * len);
// 	// map->note = ft_strcpy(map->note, &line[i]);
// 	// ft_printf("#%s\n", map->note);
// 	ft_printf("%s\n", line);
// 	// ft_strdel(&line);//either here or in parse_input.
// }

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
