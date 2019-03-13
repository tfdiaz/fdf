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

CFLAGS = -Wall -Wextra -Werror

MLXFLAGS = -framework OpenGl -framework AppKit

SRC =	src/main.c src/user_changes.c src/user_shifts.c src/keypress.c \
		src/line_algo.c src/parse_map.c src/parse_utilities.c src/draw_line.c \
		src/draw_update.c src/projection.c src/misc.c

OBJS = $(SRC:.c=.o)

LIBDIR = libft

MLXDIR = minilibx_macos

LIB = -L $(LIBDIR) -lft

MLXLIB = -L $(MLXDIR) -lmlx

$(NAME): $(OBJS) libf mlx
	$(CC) $(CFLAGS) $(MLXLIB) $(LIB) $(MLXFLAGS) $(OBJS) -o $(NAME)

libf:
	@$(MAKE) -C $(LIBDIR)

mlx:
	@$(MAKE) -C $(MLXDIR)

.PHONY: clean fclean all re debug

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBDIR) clean
	@$(MAKE) -C $(MLXDIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBDIR) fclean
	@$(MAKE) -C $(MLXDIR) fclean

all: $(NAME) $(NAME2)

re: fclean all
