# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/12 05:30:07 by skrabby           #+#    #+#              #
#    Updated: 2019/11/15 10:39:38 by skrabby          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visualizer

SRCS = main.c \
	   draw.c \
	   draw_map.c \
	   parse_data.c \
	   other.c \

FLAGS = -Wall -Werror -Wextra -I./

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@gcc -o $(NAME) $(FLAGS) $(OBJ) -L./minilibx/ -lmlx -framework OpenGL -framework AppKit ../libft/libft.a
	@tput setaf 5; tput bold; echo "..DONE Compiling Visualizer! :]"
clean:
	@rm -f $(OBJ)
	@tput setaf 5; tput bold; echo "..DONE Clean Visualizer! :]"
fclean: clean
	@rm -f $(NAME)
	@tput setaf 5; tput bold; echo "..DONE Fclean Visualizer! :]"

re: fclean all