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
		if (ft_isdigit((char)*line) && k == 0)
			k = get_ants(line, map);
		else if (*line == '#' && *(line + 1) == '#')
			i = commands(line, node, map, i);
		else if (*line == '#')
			comments(line);
		else if (!ft_strstr(line, "-"))
			i = set_nodes(line, node, map, i);
		else
			set_link(line, head, node);
		// ft_strdel(&line);
		if (g_error == -1)
			return (NULL);
	}
	if (!(map->end || map->start))
		return (NULL);
	set_distance(map);
	return (head);
}

int		get_ants(char *line, t_map *map)
{
	map->n_ants = ft_atoi(line);
	ft_printf("%d\n", map->n_ants);
	ft_strdel(&line);
	return (1);
}

int		commands(char *line, t_node *node, t_map *map, int i)
{
	if ((ft_strequ(line, "##start") == 1 || ft_strequ(line, "##end") == 1))
	{
		ft_printf("%s\n", line);
		i = ft_strequ(line, "##start") ? 1 : 2;
		ft_strdel(&line);
		get_next_line(0, &line);
		if (*line == '#' || *line == 'L')
		{
			g_error = -1;
			ft_strdel(&line);
			return (g_error);
		}
		set_nodes(line, node, map, i);
	}
	return (0);
}

void	comments(char *line)
{
	ft_printf("%s\n", line);
	ft_strdel(&line);
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
			if (temp->node->is_set == FALSE)//maybe add in to if (if) the node number exists but is larger.
				enqueue(&front, &rear, temp, current);
			temp = temp->next;
		}
		if (!front)
			return ;
		current = front->node;
		dequeue(&front);
	}
}
