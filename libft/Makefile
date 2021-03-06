# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnederlo <jnederlo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/02 13:41:01 by jnederlo          #+#    #+#              #
#    Updated: 2017/07/31 15:03:33 by jnederlo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a
CC			=	gcc
FLAGS		=	-Wall -Werror -Wextra -I includes
FILES		=	ft_atoi.c \
				ft_strcat.c \
				ft_strncat.c \
				ft_strcmp.c \
				ft_strncmp.c \
				ft_strcpy.c \
				ft_strncpy.c \
				ft_strlen.c \
				ft_strstr.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strdup.c \
				ft_isprint.c \
				ft_isdigit.c \
				ft_isalpha.c \
				ft_isalnum.c \
				ft_isascii.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_strnstr.c \
				ft_memset.c \
				ft_bzero.c \
				ft_memcpy.c \
				ft_memccpy.c \
				ft_memmove.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_strclr.c \
				ft_strequ.c \
				ft_strnequ.c \
				ft_memalloc.c \
				ft_memdel.c \
				ft_strnew.c \
				ft_strdel.c \
				ft_striter.c \
				ft_striteri.c \
				ft_strmap.c \
				ft_strmapi.c \
				ft_strsub.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_putchar.c \
				ft_putstr.c \
				ft_putendl.c \
				ft_putnbr.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_itoa.c \
				ft_strsplit.c \
				ft_lstnew.c \
				ft_lstdelone.c \
				ft_lstdel.c \
				ft_strlcat.c \
				ft_word_copy.c \
				ft_count_words.c \
				ft_next_word.c \
				ft_is_whitespace.c \
				ft_count_digits.c \
				ft_lstadd.c \
				ft_lstiter.c \
				ft_lstmap.c \
				ft_linetrim.c \
				ft_linestrip.c \
				get_next_line.c \
				ft_printf.c \
				badge_set.c \
				dispatcher.c \
				padding.c \
				cs_func_lc_cs_uc_cs.c \
				cs_func_doux.c \
				cs_func_p_ps.c \
				cs_func_uc_doux.c \
				cs_d_start.c \
				cs_d_print.c \
				cs_d_helpers.c \
				cs_u_start.c \
				cs_u_print.c \
				cs_u_helpers.c \
				cs_o_start.c \
				cs_o_print.c \
				cs_x_start.c \
				cs_x_print.c \
				cs_c_print.c \
				cs_uc_c_print.c \
				cs_s_print.c \
				cs_uc_s_print.c \
				wide_char.c \
				cs_uc_x_start.c \
				cs_uc_x_print.c \
				cs_uc_duo.c \
				cs_p_print.c \

SOURCES		=	$(addprefix srcs/, $(FILES))
OBJECTS		=	$(addprefix build/, $(FILES:.c=.o))

.PHONY: clean fclean all re

all:	$(NAME)

clean:
	@rm -rf build

fclean: clean
	@rm -f $(NAME)

re: fclean all

$(NAME): $(OBJECTS)
	@ar rcs $@ $(OBJECTS)

build:
	@mkdir build/

build/%.o: srcs/%.c | build
	@$(CC) $(FLAGS) -c $< -o $@
