/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   march_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 11:09:48 by jnederlo          #+#    #+#             */
/*   Updated: 2017/09/21 17:47:25 by jnederlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		march(t_map *map, t_node *head, t_node *node, int i)
{
	t_link	*temp;
	int		k;
	int		size;

	k = 0;
	size = (map->n_ants * map->n_ants * map->node_num);
	size = size > 200 ? 200 : size;
	while (head)
	{
		march_on(&head);
		if (head == NULL && k == size)
			break ;
		else if (head == NULL)
		{
			k++;
			head = node;
		}
		temp = head->link;
		i = move_ants(&temp, &head, map, i);
		head = head->next;
		if (head == NULL && k++ < (size + 1))
			head = node;
	}
	reset_node(node);
	ft_printf("\n");
	return (i);
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
				(*head)->was_visited == FALSE &&
				(*temp)->node->is_full == FALSE)
		{
			if ((*head) == map->start)
			{
				(*head)->ant_num = i;
				i++;
			}
			(*head)->num_ants--;
			(*head)->is_full = FALSE;
			(*temp)->node->ant_num = (*head)->ant_num;
			(*temp)->node->num_ants++;
			(*temp)->node->is_full = TRUE;
			(*temp)->node->was_visited = TRUE;
			(*temp)->node->is_end ? node_is_end((*temp)->node, map) : 0;
			if (map->new_turn == FALSE)
				ft_printf(" ");
			map->new_turn = FALSE;
			ft_printf("L%d-%s", (*temp)->node->ant_num, (*temp)->node->name);
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
		node->was_visited = FALSE;
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
