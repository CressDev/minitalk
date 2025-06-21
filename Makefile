# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cress <cress@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/23 18:21:37 by amonteag          #+#    #+#              #
#    Updated: 2025/06/21 17:35:44 by cress            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

NAME_S = server
NAME_C = client
SRC_S = server.c
SRC_C = client.c
OBJ_S = $(SRC_S:.c=.o)
OBJ_C = $(SRC_C:.c=.o)

all: $(NAME_S) $(NAME_C)

$(NAME_S): $(LIBFT) $(OBJ_S)
	@echo "Creando $(NAME_S)"
	$(CC) $(CFLAGS) $(OBJ_S) $(LIBFT) -o $(NAME_S)

$(NAME_C): $(LIBFT) $(OBJ_C)
	@echo "Creando $(NAME_C)"
	$(CC) $(CFLAGS) $(OBJ_C) $(LIBFT) -o $(NAME_C)

$(LIBFT):
	make -C $(LIBFT_DIR) bonus

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_C) $(OBJ_S)
	make -C $(LIBFT_DIR) clean
##@echo "Archivos printf .o eliminados"

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME_C) $(NAME_S) $(OBJ_S) $(OBJ_C)
##@echo "$(NAME) eliminada"

re: fclean all