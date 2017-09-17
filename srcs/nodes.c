/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 15:18:16 by jnederlo          #+#    #+#             */
/*   Updated: 2017/09/15 16:33:45 by jnederlo         ###   ########.fr       */
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
	int		name_len;
	char	*name;
	int		count;

	ft_printf("%s\n", line);
	if (i > 0)
		i = start_end(node, i);
	name = ft_word_copy(line, ' ');
	name_len = ft_strlen(name) + 1;
	node->name = name;
	node->num_ants = 0;
	line += name_len;
	node->x_coord = ft_atoi(line);
	count = ft_count_digits(node->x_coord) + 1;
	line += count;
	node->y_coord = ft_atoi(line);
	// count += ft_count_digits(node->y_coord);
	node->link = NULL;
	line -= name_len + count;
	if (node->is_end == TRUE)
		map->end = node;
	if (node->is_start == TRUE)
	{
		map->start = node;
		map->start->num_ants = map->n_ants;
	}
	map->node_num++;
	ft_strdel(&line);
	return (0);

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

void	clear_node(t_map *map)
{
	map->node->x_coord = -1;
	map->node->y_coord = -1;
	map->node->is_full = FALSE;
	map->node->is_start = FALSE;
	map->node->is_end = FALSE;
}