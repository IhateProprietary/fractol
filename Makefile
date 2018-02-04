#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jye <marvin@42.fr>                         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/15 05:30:03 by jye               #+#    #+#              #
#    Updated: 2018/02/04 01:51:07 by jye              ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc
CFLAGS = -Wall -Wextra
DFLAGS = -g3
LIBLINK = -Lminilibx_macos -lmlx -framework AppKit -framework OpenCL -framework OpenGL\
          -Llib -lft -Lft_printf -lftprintf
HEADLINK = -Isrc -Ilib

SRC_PATH = src
OBJ_PATH = obj

SRC_FILE = draw_f.c fractals.c ft_getopt_long.c ft_getopt_long1.c ihate_norm.c \
		   init.c init_opencl.c main.c move.c some_event.c zoom.c color.c frac.c \
		   hash_string.c option_parse.c
OBJ_FILE = $(addprefix $(OBJ_PATH)/, \
		   $(addsuffix .o, \
		   $(basename $(SRC_FILE))))

NAME = fractol

all: $(NAME)

$(NAME): $(OBJ_FILE) minilibx_macos/libmlx.a ft_printf/libftprintf.a lib/libft.a
	$(CC) $(OBJ_FILE) $(LIBLINK) -o $(NAME)

minilibx_macos/libmlx.a:
	make -C minilibx_macos

ft_printf/libftprintf.a:
	make -C ft_printf

lib/libft.a:
	make -C lib

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c -o $@ $< $(HEADLINK)

clean:
	rm -rf $(OBJ_FILE)
	make -C lib fclean
	make -C minilibx_macos clean
	make -C ft_printf clean

fclean: clean
	rm -rf $(NAME)

re: fclean all
