# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acaryn <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/30 11:24:21 by acaryn            #+#    #+#              #
#    Updated: 2020/12/02 22:13:07 by acaryn           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minirt
CFLAGS = -Wall -Wextra -Werror
SRCDIR = functions/
SRCS =	main.c \
		$(addprefix $(SRCDIR), \
		intersection.c \
		intersection_cylinder.c \
		numbers.c \
		parsing_head.c \
		parsing_objects.c \
		parsing_utils.c \
		parsing.c \
		screenshot.c \
		struct_free.c \
		struct_init.c \
		traceray.c \
		utils.c \
		utils2.c \
		vector_utils.c)

FILE_HEAD = includes/minirt.h
HEAD =	includes \
		includes/mlx \
		includes/get_next_line
HEADERS = $(addprefix -I , $(HEAD))
FLAG_MLX = -lmlx -framework OpenGL -framework AppKit libmlx.dylib
FLAG_GNL = libgnl.a

all: $(NAME)

$(NAME): $(SRCS) $(FILE_HEAD)
	@$(MAKE) -C includes/mlx
	@$(MAKE) -C includes/get_next_line
	mv includes/mlx/libmlx.dylib ./
	mv includes/get_next_line/libgnl.a ./
	gcc $(CFLAGS) $(SRCS) $(HEADERS) $(FLAG_MLX) $(FLAG_GNL) -o $(NAME)

clean:
	rm -rf includes/mlx/*.o
	rm -rf includes/get_next_line/obj
	rm -rf libmlx.dylib
	rm -rf libgnl.a

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
