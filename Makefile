CC = cc
NAME = fdf
FLAGS = -Wall -Wextra -Werror 
MFLAGS = -lmlx -lXext -lX11 -lm -g3
HEADER = pipex.h
SRC = pixel.c parsing_fdf.c gnl/get_next_line.c gnl/get_next_line_utils.c \
	  key_hook.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	make -C Libft
	make bonus -C Libft
	$(CC) $(OBJ) $(FLAGS) $(MFLAGS) -o $(NAME) -L. Libft/libft.a

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -f $(OBJ)
	make clean -C Libft

fclean : clean
	rm -f $(NAME)
	make fclean -C Libft

re : fclean all
	make re -C Libft
