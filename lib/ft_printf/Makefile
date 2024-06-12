# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/13 11:03:31 by mhummel           #+#    #+#              #
#    Updated: 2024/04/29 11:15:21 by mhummel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar

CFILES =	ft_printf.c \
			ft_putchar_fd_printf.c \
			ft_putstr_fd_printf.c \
			ft_putnbr_fd_printf.c \
			ft_putnbr_base_p_printf.c \
			ft_putnbr_base_u_printf.c \
			ft_putnbr_base_x_printf.c \
			ft_strlen_printf.c \
			ft_error_printf.c

OFILES = $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	$(AR) rcs $(NAME) $(OFILES)

%.o: %.c
	$(CC) -c $(CFLAGS) $?

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME) $(OBFILES)

re: fclean all

.PHONY: all clean fclean re
