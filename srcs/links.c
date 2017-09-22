/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 15:18:01 by jnederlo          #+#    #+#             */
/*   Updated: 2017/09/21 17:46:43 by jnederlo         ###   ########.fr       */
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
void	set_link(char *line, t_node *head, t_node *node, t_map *map)
{
	char	*node_name;
	char	*link_name;
	t_link	*link;
	t_node	*copy;
	int		i;

	i = 0;
	if (!map->end || !map->start)
	{
		ft_strdel(&line);
		g_error = -1;
		return ;
	}
	if (*line == '\n')
		return ;
	if (*line == '#')
	{
		ft_printf("%s\n", line);
		return ;
	}
	copy = head;
	ft_printf("%s\n", line);
	node_name = ft_word_copy(line, '-');
	i = ft_strlen(node_name) + 1;
	link_name = ft_strdup(&line[i]);
	head = traverse_list(head, node_name);
	node = traverse_list(node, link_name);
	head->num_links++;
	link = link_list(head, head->link);
	link->node = node;
	if (head->num_links == 1)
		head->link = link;
	ft_strdel(&link_name);
	ft_strdel(&node_name);
	reverse_link(head, node);
	ft_strdel(&line);
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
