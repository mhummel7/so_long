# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/11 08:35:58 by mhummel           #+#    #+#              #
#    Updated: 2024/07/09 13:05:27 by mhummel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= so_long
CFLAGS		:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX		:= ./lib/MLX42
LIBFT		:= ./lib/libft

HEADERS		:= -I ./include -I $(LIBMLX)/include -I $(LIBFT)
LIBS		:= $(LIBFT)/libft/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS		:= $(shell find ./src -iname "*.c")
OBJS		:= ${SRCS:.c=.o}

all: libft libmlx $(NAME)
	@echo " "
	@echo "\033[38;5;214m"Start the game with ./so_long maps/MAP_OF_CHOICE.ber "\033[0m"

libft:
	@make -C $(LIBFT)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
	@echo "\033[32m" Compiled "$<""\033[0m"

$(NAME): libft $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@rm -rf $(LIBMLX)/build
	@make -C $(LIBFT) clean
	@echo "\033[38;5;214m" Cleaned MLX42"\033[0m"
	@echo "\033[38;5;214m" Cleaned so_long"\033[0m"

fclean:
	@rm -f $(NAME)
	@rm -f $(OBJS)
	@rm -rf $(LIBMLX)/build
	@make -C $(LIBFT) fclean
	@echo "\033[38;5;214m" Fcleaned MLX42"\033[0m"
	@echo "\033[38;5;214m" Fcleaned $(NAME)"\033[0m"

re: fclean all

.PHONY: all clean fclean re libft libmlx
