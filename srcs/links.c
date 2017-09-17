/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 15:18:01 by jnederlo          #+#    #+#             */
/*   Updated: 2017/09/15 14:47:27 by jnederlo         ###   ########.fr       */
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
void	set_link(char *line, t_node *head, t_node *node)
{
	char	*node_name;
	char	*link_name;
	t_link	*link;
	t_node	*copy;
	int		i;

	i = 0;
	if (*line == '\n')
		return ;
	if (*line == '#')
	{
		ft_printf("%s\n", line);
		return ;
	}
	copy = head;
	//maybe free node_name??
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
	// line -= ft_strlen(node_name) + 1;
	ft_strdel(&link_name);
	ft_strdel(&node_name);
	// ft_strdel(&line);
	reverse_link(head, node);
	// next_link(head, node, copy, map);
	ft_strdel(&line);
}

// void	first_link(char *line, t_node *head, t_node *node)
// {
// 	char	*node_name;
// 	char	*link_name;
// 	t_link	*link;
// 	t_node	*copy;
// 	int		i;

// 	i = 0;
// 	copy = head;
// 	ft_printf("%s\n", line);
// 	node_name = ft_word_copy(line, '-');
// 	i = ft_strlen(node_name) + 1;
// 	link_name = ft_strdup(&line[i]);
// 	head = traverse_list(head, node_name);
// 	node = traverse_list(node, link_name);
// 	head->num_links++;
// 	link = link_list(head, head->link);
// 	link->node = node;
// 	if (head->num_links == 1)
// 		head->link = link;
// 	// line -= ft_strlen(node_name) + 1;
// 	ft_strdel(&link_name);
// 	ft_strdel(&node_name);
// 	// ft_strdel(&line);
// 	reverse_link(head, node);
// 	// next_link(head, node, copy, map);
// }


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

// /*
// ** Reads in the next link from the input - I'm basically using a
// ** recursive call in 'set_link()'
// */
// void	next_link(t_node *head, t_node *node, t_node *copy)
// {
// 	char	*line;
// 	char	*line_copy;

// 	line = NULL;
// 	while (get_next_line(0, &line) > 0)
// 	{
// 		// ft_printf("line in next_link = %s\n", line);
// 		head = copy;
// 		node = copy;
// 		if (*line == '#')
// 		{
// 			comments(line);
// 			ft_strdel(&line);
// 			get_next_line(0, &line);
// 		}
// 		line_copy = ft_strdup(line);
// 		ft_strdel(&line);
// 		// ft_printf("line in next_link = %s\n", line);
// 		set_link(line_copy, head, node);
// 		ft_strdel(&line_copy);
// 	}
// 	// ft_strdel(&line);
// }



