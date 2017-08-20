/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 15:18:16 by jnederlo          #+#    #+#             */
/*   Updated: 2017/08/19 15:19:30 by jnederlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_node	*node_list(char **line, t_map *map, t_node *head)
{
	t_node	*node;
	int		node_num;

	if (ft_strstr(*line, "-"))
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

void	set_nodes(char **line, t_node *node, t_map *map)
{
	int		name_len;
	char	*name;
	int		count;

	name = ft_word_copy(*line, ' ');
	name_len = ft_strlen(name) + 1;
	node->name = ft_memalloc(sizeof(char) * name_len);
	node->name = name;
	*line += name_len;
	node->x_coord = ft_atoi(*line);
	count = ft_count_digits(node->x_coord) + 1;
	*line += count;
	node->y_coord = ft_atoi(*line);
	count += ft_count_digits(node->y_coord);
	node->link = NULL;
	*line -= name_len + count;
	if (node->is_end == TRUE)
		map->end = node;
	if (node->is_start == TRUE)
		map->start = node;
	map->node_num++;
}

void	clear_node(t_map *map)
{
	map->node->x_coord = -1;
	map->node->y_coord = -1;
	map->node->is_full = FALSE;
	map->node->is_start = FALSE;
	map->node->is_end = FALSE;
}