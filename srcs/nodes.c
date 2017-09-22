/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 15:18:16 by jnederlo          #+#    #+#             */
/*   Updated: 2017/09/21 16:35:33 by jnederlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Sets up the linked list structure for the nodes as they are read in from
** the input. It will then add nodes to the linked list as it continues
** reading in from the input for each new node.
*/
t_node	*node_list(char *line, t_map *map, t_node *head)
{
	t_node	*node;
	int		node_num;

	if (ft_strstr(line, "-"))
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

int		set_nodes(char *line, t_node *node, t_map *map, int i)
{
	if (i == 1)
		node->is_start = TRUE;
	else if (i == 2)
	{
		node->is_end = TRUE;
		node->is_set = TRUE;
		node->distance = 0;
	}
	i = set_node_params(line, node, map);
	if (g_error == -1)
		ft_strdel(&line);
	if (node->is_end == TRUE)
		map->end = node;
	if (node->is_start == TRUE)
	{
		map->start = node;
		map->start->num_ants = map->n_ants;
	}
	map->node_num++;
	return (0);
}

int		set_node_params(char *line, t_node *node, t_map *map)
{
	char	*name;
	int		i;

	if (*line == '#' || *line == 'L')
		return (g_error = -1);
	name = ft_word_copy(line, ' ');
	i = ft_strlen(name) + 1;
	node->name = name;
	node->num_ants = 0;
	i += valid_coord(line, i);
	node->x_coord = ft_atoi(&line[i]);
	i += ft_count_digits(node->x_coord) + 1;
	i += valid_coord(line, i);
	node->y_coord = ft_atoi(&line[i]);
	i += ft_count_digits(node->y_coord);
	duplicate_name(node, map);
	if (line[i] != 0 || g_error == -1)
		return (g_error = -1);
	ft_printf("%s\n", line);
	ft_strdel(&line);
	node->link = NULL;
	return (0);
}

void	duplicate_name(t_node *node, t_map *map)
{
	t_node	*head;

	head = map->node;
	while (head)
	{
		if (ft_strequ(node->name, head->name) &&
			node->x_coord != head->x_coord &&
			node->y_coord != head->y_coord)
		{
			g_error = -1;
			return ;
		}
		head = head->next;
	}
}

int		valid_coord(char *line, int i)
{
	int	k;

	k = i;
	i = 0;
	if (line[k] == '-')
	{
		k++;
		i = 1;
	}
	if (!ft_isdigit(line[k]))
		g_error = -1;
	return (i);
}
