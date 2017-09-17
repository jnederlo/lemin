/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lemin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 10:46:41 by jnederlo          #+#    #+#             */
/*   Updated: 2017/09/15 17:09:40 by jnederlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		main()
{
	t_map	*map;
	t_node	*head;
	t_node	*node;

	map = ft_memalloc(sizeof(t_map));
	//maybe add error check for valid file??
	head = parse_input(map);
	if (head == NULL)
	{
		ft_printf("ERROR\n");
		return (0);
	}
	node = head;
	ft_printf("\n");
	while (map->n_ants > 0)
		march(map, head, node);
	// free_up(head);
	// free(head);
	// free(map);
	// while (1);
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

void	free_up(t_node *head)
{
	while (head)
	{
		while (head->link)
		{
			free(head->link);
			head->link = head->link->next;
		}
		free(head->name);
		head = head->next;
	}
}
