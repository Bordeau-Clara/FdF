# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbordeau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/08 16:10:04 by cbordeau          #+#    #+#              #
#    Updated: 2025/02/05 09:06:15 by cbordeau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
NAME = libft.a
FLAGS = -Wall -Werror -Wextra
HEADER = libft.h
SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
      ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
      ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
      ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
      ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c \
      ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
      ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_atoi_base.c \
      get_next_line.c get_next_line_utils.c

OBJ = $(SRC:.c=.o)

SRC_BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstlast_bonus.c \
	    ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c \
	    ft_lstiter_bonus.c ft_lstmap_bonus.c ft_lstsize_bonus.c

OBJ_BONUS = $(SRC_BONUS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

bonus : .
. : $(NAME) $(OBJ_BONUS)
	ar rc $(NAME) $(OBJ_BONUS)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@
clean :
	rm -f $(OBJ)
	rm -f $(OBJ_BONUS)
fclean : clean
	rm -f $(NAME)
re : fclean all
.PHONY : all bonus clean fclean re
