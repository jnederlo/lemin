/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   march_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 11:09:48 by jnederlo          #+#    #+#             */
/*   Updated: 2017/09/14 12:06:19 by jnederlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	march(t_map *map, t_node *head, t_node *node)
{
	t_link	*temp;
	int		i;
	int		k;

	k = 0;
	i = 1;
	while (head)
	{
		march_on(&head);
		if (head == NULL)
			break ;
		temp = head->link;
		i = move_ants(&temp, &head, map, i);
		head = head->next;
		if (head == NULL && k++ < 2)
			head = node;
	}
	reset_node(node);
	ft_printf("\n");
	i = 1;
}

void	march_on(t_node **head)
{
	while (*head)
	{
		if ((*head)->was_visited == TRUE)
			*head = (*head)->next;
		else
			return ;
	}
}

int		move_ants(t_link **temp, t_node **head, t_map *map, int i)
{
	while (*temp)
	{
		if ((*head)->num_ants > 0 &&
				(*temp)->node->distance < (*head)->distance &&
				(*temp)->node->was_visited == FALSE &&
				(*temp)->node->is_full == FALSE)
		{
			(*head)->num_ants--;
			(*head)->is_full = FALSE;
			(*temp)->node->num_ants++;
			(*temp)->node->is_full = TRUE;
			(*temp)->node->was_visited = TRUE;
			(*temp)->node->is_end ? node_is_end((*temp)->node, map) : 0;
			i > 1 ? ft_printf(" ") : 0;
			ft_printf("L%d-%s", i, (*temp)->node->name);
			i++;
		}
		*temp = (*temp)->next;
	}
	return (i);
}

void	node_is_end(t_node *node, t_map *map)
{
	if (node->is_end == TRUE)
	{
		map->n_ants--;
		node->is_full = FALSE;
	}
}

void	reset_node(t_node *node)
{
	t_node	*temp;

	temp = node;
	while (temp)
	{
		temp->was_visited = FALSE;
		temp = temp->next;
	}
}
