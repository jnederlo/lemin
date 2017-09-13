/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lemin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 10:46:41 by jnederlo          #+#    #+#             */
/*   Updated: 2017/09/13 11:11:57 by jnederlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		main(int argc, char **argv)
{
	char	*line;
	t_map	*map;
	t_node	*head;
	t_node	*node;

	map = ft_memalloc(sizeof(t_map));
	(void)argc;
	// if (argc != 2)
	// 	return (ft_printf("Error\n"));
	line = argv[1];
	head = parse_input(&line, map);
	node = head;
	while (map->n_ants > 0)
		march(map, head, node);
	return (0);
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
