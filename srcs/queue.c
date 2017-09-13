/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 11:06:12 by jnederlo          #+#    #+#             */
/*   Updated: 2017/09/13 11:06:41 by jnederlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	enqueue(t_queue **front, t_queue **rear, t_link *link, t_node *current)
{
	t_queue *new_node;
	t_node	*node;

	node = link->node;
	new_node = ft_memalloc(sizeof(t_queue));
	new_node->node = node;
	node->distance = current->distance + 1;
	node->is_set = TRUE;
	new_node->next = NULL;
	if (*front == NULL)
	{
		*rear = new_node;
		*front = *rear;
	}
	else
	{
		(*rear)->next = new_node;
		*rear = new_node;
	}
}

void	dequeue(t_queue **front)
{
	t_queue	**temp;

	if (*front != NULL)
	{
		temp = front;
		*front = (*front)->next;
	}
}
