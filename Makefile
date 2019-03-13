# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/18 10:50:08 by tdiaz             #+#    #+#              #
#    Updated: 2018/09/18 11:33:58 by tdiaz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = @gcc

FLAGS = -Wall -Wextra -Werror

MLXFLAGS = -L minilibx_macos/ -lmlx -framework OpenGL -framework AppKit

SRC =	src/main.c src/user_changes.c src/user_shifts.c src/keypress.c \
		src/line_algo.c src/parse_map.c src/parse_utilities.c src/draw_line.c \
		src/draw_update.c src/projection.c src/misc.c

OBJS = $(SRC:.c=.o)

LIBDIR = libft

MLXDIR = minilibx_macos

LIB = -L libft/ -lft

$(NAME): $(OBJS) $(LIB) $(MLX)
	$(CC) $(CFLAGS) $(LIB) $(MLXFLAGS) minilibx_macos/libmlx.a $(OBJS) -o $(NAME)

$(LIB):
	@make -C $(LIBDIR)

$(MLX):
	@make -C $(MLXDIR) all

.PHONY: clean fclean all re debug

debug: $(SRC) $(LIB)
	$(CC) -o debug -g $(SRC) $(LIB) $(MLXFLAGS)

clean:
	@cd/src rm -f $(OBJS)
	@make -C $(LIBDIR) clean
	@make -C $(MLXDIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBDIR) fclean

all: $(NAME) $(NAME2)

re: fclean all
