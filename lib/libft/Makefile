# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/13 11:03:31 by mhummel           #+#    #+#              #
#    Updated: 2024/07/02 10:39:53 by mhummel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar

# Libft files
LIBFT_DIR = libft/
LIBFT_FILES =	ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_itoa.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_split.c \
			ft_strcpy.c \
			ft_strncpy.c

# ft_printf files
FT_PRINTF_DIR = ft_printf/
FT_PRINTF_FILES =	ft_printf.c \
			ft_putchar_fd_printf.c \
			ft_putstr_fd_printf.c \
			ft_putnbr_fd_printf.c \
			ft_putnbr_base_p_printf.c \
			ft_putnbr_base_u_printf.c \
			ft_putnbr_base_x_printf.c \
			ft_strlen_printf.c \
			ft_error_printf.c

# get_next_line files
GNL_DIR = get_next_line/
GNL_FILES =	get_next_line.c \
			get_next_line_utils.c

SRCS =	$(addprefix $(LIBFT_DIR), $(LIBFT_FILES)) \
		$(addprefix $(FT_PRINTF_DIR), $(FT_PRINTF_FILES)) \
		$(addprefix $(GNL_DIR), $(GNL_FILES))

OBJS= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) -r $@ $?

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR) -I$(GNL_DIR)
	@echo "\033[32m" Compiled "$<" "\033[0m"

clean:
	@rm -f $(OBJS)
	@echo "\033[38;5;214m" Cleaned libft"\033[0m"

fclean:
	@rm -f $(OBJS)
	@rm -f $(NAME)
	@echo "\033[38;5;214m" Fcleaned $(NAME) "\033[0m"

re: fclean all

.PHONY: all clean fclean re