/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 15:18:16 by jnederlo          #+#    #+#             */
/*   Updated: 2017/09/18 13:52:20 by jnederlo         ###   ########.fr       */
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

/*
** fills in the following struct fields for each node:
**	- name
**	- x_coord
**	- y_coord
**	- link
**
** increases the map->node_num count by 1 (used in node linked list).
*/
int		set_nodes(char *line, t_node *node, t_map *map, int i)
{
	if (i > 0)
		i = start_end(node, i);
	i = set_node_params(line, node);
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

int		set_node_params(char *line, t_node *node)
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
	if (line[i] != 0 || g_error == -1)
		return (g_error = -1);
	ft_printf("%s\n", line);
	ft_strdel(&line);
	node->link = NULL;
	return (0);
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

int		start_end(t_node *node, int i)
{
	if (i == 1)
		node->is_start = TRUE;
	else
	{
		node->is_end = TRUE;
		node->is_set = TRUE;
		node->distance = 0;
	}
	return (0);
}
