/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 10:21:10 by jnederlo          #+#    #+#             */
/*   Updated: 2017/09/19 16:07:54 by jnederlo         ###   ########.fr       */
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
	t_bool			was_visited;
	t_bool			is_start;
	t_bool			is_end;
	t_bool			is_set;
	int				ant_num;
	char			*name;
	int				num_ants;
	int				node_num;
	int				num_links;
	int				distance;
	struct s_link	*link;
	struct s_node	*next;
}					t_node;

typedef struct		s_link
{
	int				link_num;
	t_node			*node;
	struct s_link	*next;
}					t_link;

typedef struct		s_queue
{
	t_node			*node;
	struct s_queue	*next;
}					t_queue;

typedef struct		s_map
{
	int				n_ants;
	t_bool			new_turn;
	t_node			*node;
	t_node			*start;
	t_node			*end;
	int				node_num;
}					t_map;

int					g_error;

/*
** Functions in parse_input.c
*/
t_node	*parse_input(t_map *map);
// void	duplicate_name(t_node *node, t_node *head);
void	map_reader(char *line, t_node *node, t_node *head, t_map *map);
int		get_ants(char *line, t_map *map);
int		commands(char *line, t_node *node, t_map *map, int i);
void	comments(char *line);
void	set_distance(t_map *map);

/*
** Functions in nodes.c
*/
t_node	*node_list(char *line, t_map *map, t_node *head);
int		set_nodes(char *line, t_node *node, t_map *map, int i);
int		set_node_params(char *line, t_node *node, t_map *map);
void	duplicate_name(t_node *node, t_map *map);
int		start_end(t_node *node, int i);
int		valid_coord(char *line, int i);

/*
** Functions in links.c
*/
void	set_link(char *line, t_node *head, t_node *node, t_map *map);
void	first_link(char *line, t_node *head, t_node *node);
t_node	*traverse_list(t_node *node, char *name);
t_link	*link_list(t_node *node, t_link *link);
void	reverse_link(t_node *node, t_node *head);
void	next_link(t_node *head, t_node *node, t_node *copy);

/*
** Functions in queue.c
*/
void	enqueue(t_queue **front, t_queue **rear, t_link *link, t_node *current);
void	dequeue(t_queue **front);

/*
** Functions in march_ants.c
*/
int		march(t_map *map, t_node *head, t_node *node, int i);
void	march_on(t_node **head);
int		move_ants(t_link **temp, t_node **head, t_map *map, int i);
void	node_is_end(t_node *node, t_map *map);
void	reset_node(t_node *node);

void	print_nodes(t_node *node);
void	free_up(t_node *head);
#endif
