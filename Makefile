# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/19 08:07:35 by cbordeau          #+#    #+#              #
#    Updated: 2025/02/21 12:25:13 by cbordeau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COMPILATION ###
CC      = cc
FLAGS  = -Wall -Wextra -Werror -g3

### EXECUTABLE ###
NAME   = fdf

### INCLUDES ###
LIBFT  = Libft
OBJ_PATH  = objs
SRC_PATH  = srcs
MLX = minilibx-linux

### SOURCE FILES ###
SOURCES = fdf.c colors.c key_hook.c key_hook_2.c parsing_fdf.c sphere.c \
		  display.c utils.c utils_2.c exit.c rotation.c parsing_utils.c

### OBJECTS ###

SRCS = $(addprefix $(SRC_PATH)/,$(SOURCES))
OBJS = $(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))

### COLORS ###
NOC         = \033[0m
BOLD        = \033[1m
UNDERLINE   = \033[4m
BLACK       = \033[1;30m
RED         = \033[1;31m
GREEN       = \033[1;32m
YELLOW      = \033[1;33m
BLUE        = \033[1;34m
VIOLET      = \033[1;35m
CYAN        = \033[1;36m
WHITE       = \033[1;37m

### RULES ###

all: lib tmp $(NAME)

lib: mlx
	@echo "$(GREEN)Creating lib files$(CYAN)"
	@make bonus -C $(LIBFT)

mlx: $(MLX)
	make -C $(MLX)

$(MLX):
	git clone https://github.com/42Paris/minilibx-linux.git $(MLX)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -L $(LIBFT) -L $(MLX) -o $@ $^ -lft -lmlx -lXext -lX11 -lm
	@echo "$(GREEN)Project successfully compiled"

tmp:
	@mkdir -p objs

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@$(CC) $(FLAGS) -c -o $@ $<
	@echo "$(BLUE)Creating object file -> $(WHITE)$(notdir $@)... $(RED)[Done]$(NOC)"

clean:
	@echo "$(GREEN)Supressing libraries files$(CYAN)"
	@make clean -C $(LIBFT)
	@rm -rf $(OBJ_PATH)

fclean:
	@echo "$(GREEN)Supressing libraries files$(CYAN)"
	@rm -rf $(OBJ_PATH)
	@rm -f $(NAME)
	@rm -rf $(MLX)
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: temporary, re, fclean, cleanCC = cc
