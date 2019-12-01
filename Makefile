# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/01 18:00:07 by spozzi            #+#    #+#              #
#    Updated: 2019/12/01 18:31:39 by spozzi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = players/spozzi.filler

SRC_NAME = main.c parse_stuff.c heatmap.c utils.c strategy.c strategy1.c \
strategy2.c strategy3.c map_parse.c piece_parse.c other_place.c \
manage_memory.c extra.c

SRC_PATH = src/
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))

FLAGS = -Wall -Wextra -Werror

HEADERS = ./header
HEAD = header/filler.h

LIBFT_PATH = includes/libft/
LIBFT = $(addprefix $(LIBFT_PATH), libft.a)

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ_PATH = obj/
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(HEAD) $(OBJ)
	@gcc $(FLAGS) -o $@ $(OBJ) -L $(LIBFT_PATH) -lft
	@echo "\n\033[1;32m---------->[FILLER IS READY]<----------- \033[0m\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEAD)
	@mkdir -p obj
	gcc $(FLAGS) -o $@ -c $< -I $(HEADERS)

clean:
	@make clean -C $(LIBFT_PATH)
	@rm -rf $(OBJ_PATH)
	@echo "\n\033[1;31m---------->[.O REMOVED]<----------- \033[0m"

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@rm -f $(NAME)
	@echo "\n\033[1;31m----------->[RTV1 REMOVED]<-------- \033[0m"

re: fclean all

.PHONY : fclean clean all re
