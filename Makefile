# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/09 00:35:59 by tkondo            #+#    #+#              #
#    Updated: 2024/12/31 02:59:40 by tkondo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
INCLUDE_DIR = -Iinclude -I./libft/include
CFLAGS = -c -fPIE -Wall -Wextra -Werror

SRC_DIR = src
OBJ_DIR = bin
LIBS = libft/libft.a
LIB_DIR = -L./libft
LFLAGS = -lft
NAME = push_swap
TARGET =\
	act_interface0\
	act_interface1\
	act_interface2\
	assert\
	compress0\
	compress1\
	dllst0\
	dllst1\
	load\
	sort_large\
	sort_small\
	std_act0\
	std_act1\
	main

OBJS = $(addprefix $(OBJ_DIR)/,$(addsuffix .o,$(TARGET)))

all: $(NAME)

dev: CFLAGS+=-O0 -g -fsanitize=address
dev: LFLAGS+=-g -fsanitize=address
dev: all

$(NAME): $(LIBS) $(OBJS)
	$(CC) $^ -o $@ $(LIB_DIR) $(LFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(INCLUDE_DIR)

libft/libft.a:
	make -C libft

clean:
	rm -f $(OBJS)
	@make -C libft fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

devre: fclean dev

.PHONY: dev devre all clean fclean re init
