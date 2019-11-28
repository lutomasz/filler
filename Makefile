NAME = filler.lupozzi

SRC = main.c parse_stuff.c heatmap.c utils.c strategy.c strategy1.c strategy2.c strategy3.c map_parse.c piece_parse.c other_place.c manage_memory.c

OBJ = main.o parse_stuff.o heatmap.o utils.o strategy.o strategy1.o strategy2.o strategy3.o map_parse.o piece_parse.o other_place.o manage_memory.o

HEADERS = filler.h

LIBRARIES =  -L libft -lft

#CFLAGS = -Wall -Wextra -Werror

CC = gcc

all: $(NAME)

$(NAME):$(OBJ)
	@make -C libft/
	@gcc $(CFLAGS) -o $(NAME) $(OBJ) $(LIBRARIES)

clean:
	@make clean -C libft/
	@/bin/rm -f $(OBJ)
	@echo cleaning

fclean: clean
	make fclean -C libft/
	@/bin/rm -f $(NAME)
	@echo fcleaning

re: fclean all

.PHONY : fclean clean all re
