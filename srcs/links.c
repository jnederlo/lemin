/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 15:18:01 by jnederlo          #+#    #+#             */
/*   Updated: 2017/09/13 11:05:17 by jnederlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Sets up the linked list structure for the links contained inside each node.
** Each link of a node is linked to every other link of the node. I used the
** linked list structure as I didn't know how many links each node had.
**
** The links point to another complete node. So the linked list internal to
** each node has links to another nodes.
*/
void	set_link(char **line, t_node *head, t_node *node)
{
	char	*node_name;
	char	*link_name;
	t_link	*link;
	t_node	*copy;

	if (**line == '\n')
		return ;
	copy = head;
	node_name = ft_word_copy(*line, '-');
	*line += ft_strlen(node_name) + 1;
	link_name = ft_strdup(*line);
	head = traverse_list(head, node_name);
	node = traverse_list(node, link_name);
	head->num_links++;
	link = link_list(head, head->link);
	link->node = node;
	if (head->num_links == 1)
		head->link = link;
	*line -= ft_strlen(node_name) + 1;
	reverse_link(head, node);
	next_link(line, head, node, copy);
}

/*
** Traverses through the main linked list structure (of nodes) to set
** the appropriate nodes as 'head' and 'node' for the links.
*/
t_node	*traverse_list(t_node *node, char *name)
{
	while (ft_strcmp(node->name, name) && node->next != NULL)
		node = node->next;
	return (node);
}

/*
** Initializes the links linked list and adds new links to the list.
*/
t_link	*link_list(t_node *node, t_link *link)
{
	t_link	*link_node;
	int		num_links;

	num_links = node->num_links;
	if (link == NULL)
	{
		link_node = ft_memalloc(sizeof(t_node));
		link_node->link_num = num_links;
		link_node->next = NULL;
		return (link_node);
	}
	while (num_links != link->link_num && link->next != NULL)
		link = link->next;
	if (num_links == link->link_num)
		return (link);
	link_node = ft_memalloc(sizeof(t_link));
	link_node->link_num = num_links;
	link->next = link_node;
	link_node->next = NULL;
	return (link_node);
}

/*
** Every link is a two way link, so I reverse the nodes to have each
** link also pointing back to the linking node.
*/
void	reverse_link(t_node *node, t_node *head)
{
	t_link	*link;

	head->num_links++;
	link = link_list(head, head->link);
	link->node = node;
	if (head->num_links == 1)
		head->link = link;
}

/*
** Reads in the next link from the input - I'm basically using a
** recursive call in 'set_link()'
*/
void	next_link(char **line, t_node *head, t_node *node, t_node *copy)
{
	while (get_next_line(0, line))
	{
		head = copy;
		node = copy;
		set_link(line, head, node);
	}
}



