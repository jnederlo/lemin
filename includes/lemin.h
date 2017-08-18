/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 10:21:10 by jnederlo          #+#    #+#             */
/*   Updated: 2017/08/17 21:55:55 by jnederlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"

typedef enum	e_bool
{
	FALSE,
	TRUE
}				t_bool;

typedef struct		s_node
{
	int				x_coord;
	int				y_coord;
	t_bool			is_full;
	t_bool			is_start;
	t_bool			is_end;
	char			*name;
	int				node_num;
	int				link_num;
	struct s_node	*next_link;
	struct s_node	*next;

}					t_node;

typedef struct		s_map
{
	int			n_ants;
	t_node		*node;
	char		*note;
	int			node_num;
	int			link_num;
}					t_map;

void	get_nodes(char **line, t_map *map);
void	commands(char **line, t_node *node, t_map *map);
void	get_ants(char **line);
void	set_nodes(char **line, t_node *node, t_map *map);
void	comments(char **line, t_map *map);
void	clear_node(t_map *map);
void	set_links(char **line, t_map *map, t_node *head, t_node *node);
t_node	*node_list(char **line, t_map *map, t_node *head);
t_node	*link_list(t_map *map, t_node *head_link);
void	print_nodes(t_node *node);
void	first_link(char **line, t_map *map, t_node *link, t_node *node);
#endif