# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccottin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/15 15:06:17 by ccottin           #+#    #+#              #
#    Updated: 2022/04/04 14:17:14 by ccottin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= so_long

SRC	= ./src/check_map.c	./src/gnl/get_next_line.c	./src/gnl/get_next_line_utils.c	\
	./src/main.c	./src/return.c ./src/utils.c ./src/init.c ./src/map.c	./src/handle_event.c

OBJ	= $(SRC:.c=.o)

CC	= gcc

CFLAG	= -Wall -Wextra	-Werror -g

all	: 	$(NAME)

%.o	:	%.c
		$(CC) $(CFLAG) -I/usr/include -Imlx_Linux -O3 -c $< -o $@

$(NAME)	:	$(OBJ)
		make -C ./mlx_Linux
		$(CC) $(OBJ) -Lmlx_Linux -lmlx_Linux -L/usr/lib -Imlx_Linux -lXext -lX11 -lm -lz -o $(NAME)

clean	: 
		make -C ./mlx_Linux clean
		rm -rf $(OBJ)

fclean	:	clean
		rm -rf $(NAME)

re	:	fclean all

.PHONY	: all clean fclean re
