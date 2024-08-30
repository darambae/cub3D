# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/28 15:55:13 by dabae             #+#    #+#              #
#    Updated: 2024/08/30 16:57:27 by dabae            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#
NAME = cub3D
BONUS = cub3D_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
GET_NEXT_LINE_DIR = get_next_line
GET_NEXT_LINE = $(wildcard $(GET_NEXT_LINE_DIR)/*.c)
SRC_MAN = $(wildcard src/mandatory/*.c)
SRC_BONUS = $(wildcard src/bonus/*.c)
OBJ_MAN = $(SRC_MAN:.c=.o) $(GET_NEXT_LINE:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o) $(GET_NEXT_LINE:.c=.o)
MLX = mlx_linux
MLXLIB = $(MLX)/libmlx_Linux.a

all: $(NAME)

$(NAME): $(LIBFT) $(MLXLIB) $(OBJ_MAN)
	$(CC) $(CFLAGS) $(OBJ_MAN) -L./libft -lft -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

$(BONUS) : $(LIBFT) $(MLXLIB) $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -L./libft -lft -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lm -lz -o $(BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -Imlx_linux -O0 -c $< -o $@

$(LIBFT):
	$(MAKE) -C ./libft

$(MLXLIB):
	$(MAKE) -C $(MLX)
		
bonus: $(BONUS)

clean:
	$(MAKE) clean -C ./libft
	@$(RM) -f $(OBJ_MAN) $(OBJ_BONUS)

fclean: clean
	$(MAKE) fclean -C ./libft 
	@$(RM) -f $(NAME) $(BONUS)

re: fclean all bonus

.PHONY: all clean fclean re