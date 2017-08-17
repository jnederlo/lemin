/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 10:21:10 by jnederlo          #+#    #+#             */
/*   Updated: 2017/08/16 19:22:17 by jnederlo         ###   ########.fr       */
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
	struct s_node	*next;
}					t_node;

typedef struct		s_map
{
	int			n_ants;
	t_node		*node;
	char		*note;
	int			node_num;
}					t_map;

void	setup_map(char **line);
void	commands(char **line, t_node *node);
void	rooms(char **line, t_node *node);
void	comments(char **line, t_map *map);
void	clear_node(t_map *map);
void	links(char **line, t_node *node);
t_node	*node_list(t_map *map, t_node *head, int status);
void	print_node(t_node *node);

#endif