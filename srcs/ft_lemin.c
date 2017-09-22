/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lemin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 10:46:41 by jnederlo          #+#    #+#             */
/*   Updated: 2017/09/21 17:41:19 by jnederlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		main()
{
	t_map	*map;
	t_node	*head;
	t_node	*node;
	int		i;

	i = 1;
	map = ft_memalloc(sizeof(t_map));
	head = parse_input(map);
	if (head == NULL)
	{
		free_up(map->node);
		free_nodes(map->node);
		ft_printf("ERROR\n");
		return (0);
	}
	node = head;
	ft_printf("\n");
	while (map->n_ants > 0)
	{
		map->new_turn = TRUE;
		i = march(map, head, node, i);
	}
	free_up(node);
	free_nodes(node);
	free(map);
	return (0);
}

void	free_nodes(t_node *node)
{
	t_node	*temp;
	t_node	*copy;

	while (node)
	{
		copy = node;
		node->next ? temp = node->next : 0;
		free(node);
		node = temp;
		if (node == copy)
			break ;
	}
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
	t_node	*temp_node;
	t_link	*temp_link;

	temp_link = NULL;
	while (head)
	{
		while (head->link)
		{
			head->link->next ? temp_link = head->link->next : 0;
			free(head->link);
			if (!temp_link)
				break ;
			head->link = temp_link;
			temp_link = NULL;
		}
		head->next ? temp_node = head->next : 0;
		ft_strdel(&(head)->name);
		if (!head->next)
			return ;
		head = temp_node;
	}
}
