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

NAME = libgnl.a
CFLAGS = -Wall -Wextra -Werror
SRCS =	get_next_line.c \
		get_next_line_utils.c \

FILE_HEAD = get_next_line.h
OBJDIR = obj/
OBJS = $(addprefix $(OBJDIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS) $(HEAD)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)%.o: %.c $(FILE_HEAD)
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
