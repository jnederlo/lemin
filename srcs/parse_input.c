/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 11:03:56 by jnederlo          #+#    #+#             */
/*   Updated: 2017/09/15 17:05:31 by jnederlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_node	*parse_input(t_map *map)
{
	t_node	*node;
	t_node	*head;
	char	*line;
	int		i;
	int		k;

	i = 0;
	k = 0;
	head = NULL;
	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		!head ? head = node_list(line, map, head) : 0;
		node = node_list(line, map, head);
		if (k == 0)
			k = get_ants(line, map, k);
		else if (*line == '#' && *(line + 1) == '#')
			i = commands(line);
		else if (*line == '#')
			ft_printf("%s\n", line);
		else if (!ft_strstr(line, "-"))
			i = set_nodes(line, node, map, i);
		else
			set_link(line, head, node);
		ft_strdel(&line);
	}
	set_distance(map);
	return (head);
}

int		get_ants(char *line, t_map *map, int k)
{
	map->n_ants = ft_atoi(line);
	ft_printf("%d\n", map->n_ants);
	return (k = 1);
}

int		commands(char *line)
{
	if ((ft_strequ(line, "##start") == 0 || ft_strequ(line, "##end") == 0))
	{
		ft_printf("%s\n", line);
		if (ft_strequ(line, "##start") == 0)
			return (1);
		else
			return (2);
	}
	else
	{
		ft_printf("ERROR\n");
		return (-1);
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
