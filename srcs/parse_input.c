/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 11:03:56 by jnederlo          #+#    #+#             */
/*   Updated: 2017/09/21 17:46:18 by jnederlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_node	*parse_input(t_map *map)
{
	t_node	*node;
	t_node	*head;
	char	*line;

	head = NULL;
	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		!head ? head = node_list(line, map, head) : 0;
		node = node_list(line, map, head);
		map->node = head;
		if (*line == 0)
		{
			ft_strdel(&line);
			return (NULL);
		}
		else
			map_reader(line, node, head, map);
		if (g_error == -1)
			return (NULL);
	}
	if (!line)
		return (NULL);
	if (!map->end->link || !map->start->link)
		return (NULL);
	set_distance(map);
	return (head);
}

void	map_reader(char *line, t_node *node, t_node *head, t_map *map)
{
	int	i;

	i = 0;
	if (!line || g_error == -1)
		return ;
	if (ft_isdigit((char)*line) && !map->n_ants)
	{
		map->n_ants = ft_atoi(line);
		ft_printf("%d\n", map->n_ants);
		ft_strdel(&line);
	}
	else if (*line == '#' && *(line + 1) == '#')
		i = commands(line, node, map, i);
	else if (*line == '#')
		comments(line);
	else if (!ft_strstr(line, "-"))
		i = set_nodes(line, node, map, i);
	else
		set_link(line, head, node, map);
}

int		commands(char *line, t_node *node, t_map *map, int i)
{
	if ((ft_strequ(line, "##start") == 1 || ft_strequ(line, "##end") == 1))
	{
		if (!map->n_ants)
			g_error = -1;
		else if (ft_strequ(line, "##start") == 1 && map->start)
			g_error = -1;
		else if (ft_strequ(line, "##end") == 1 && map->end)
			g_error = -1;
		if (g_error == -1)
		{
			ft_strdel(&line);
			return (g_error);
		}
		ft_printf("%s\n", line);
		i = ft_strequ(line, "##start") ? 1 : 2;
		ft_strdel(&line);
		get_next_line(0, &line);
		if (*line == '#' || *line == 'L')
		{
			ft_strdel(&line);
			return (g_error = -1);
		}
		set_nodes(line, node, map, i);
	}
	else
		ft_strdel(&line);
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
