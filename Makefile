
NAME = filler.lutomasz

SRC = main.c

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -c -Wall -Wextra -Werror -o3

PLIBFT = libft/


all : $(NAME)

$(NAME) :
	make -C $(PLIBFT)
	@#$(CC) $(CFLAGS) $(SRC) $(INC)
	@#$(CC) -o $(NAME) $(OBJ) -L minilibx_macos $(DINC) $(FRAME)
	gcc -o $(NAME) main.c parting.c -L. libft/libft.a 
	make clean
	echo "Compiled"

clean :
	@make clean -C $(PLIBFT)
	@/bin/rm -f $(OBJ)

fclean :
	@/bin/rm -f $(OBJ)
	@/bin/rm -f $(NAME)
	@make fclean -C $(PLIBFT)

re : fclean all

.PHONY: all clean fclean re
