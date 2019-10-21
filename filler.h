/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <lutomasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 20:06:29 by lutomasz          #+#    #+#             */
/*   Updated: 2019/10/18 17:04:28 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libft/libft.h"
#include "libft/get_next_line.h"

# define BUF_SIZE 10000

typedef struct s_first_x
{
	int x;
	int y;
}				t_first_x;

typedef struct s_first_o
{
	int x;
	int y;
}				t_first_o;

typedef struct s_last_played_x
{
	int x;
	int y;
}				t_last_played_x;

typedef struct s_last_played_o
{
	int x;
	int y;
}				t_last_played_o;

typedef struct s_shift
{
	int up;
	int left;
	int down;
	int right;

}				t_shift;

typedef struct s_piece
{
	int h;
	int w;
	int first_x;
	int first_y;
	int last_x;
	int last_y;
	int total;

}				t_piece;

typedef struct 	s_struct
{
	//gestion map;
	int map_w;
	int map_h;
	int fd;
	char **map;
	char symbol;
	char c;
	char my_c[2];
	char his_c[2]; //0 -> o 1 -> O
	//gestion situation
	bool first_x_on;
	bool first_o_on;
	bool last_played_x_on;
	bool last_played_o_on;

	int 	player1 : 3;
	char	*en;
	char	*me;

	char **shape;
	char **tmp_shape;
	int **coord;
	char **map_cpy;

	t_piece 	piece;
	t_shift		shift;
	t_first_o 	first_o;
	t_first_x 	first_x;
	t_last_played_x last_played_x;
	t_last_played_o last_played_o;
	t_first_o	first_en;
	t_first_o	last_played_en;
}				t_struct;

typedef struct s_elem
{

	int debut_y;
	int debut_x;

	int last_pos_x;
	int last_pos_y;

	int middle_y;
	int middle_x;
}						t_elem;

t_struct *init_utils(char *map);
int ft_get_size_map(t_struct *utils);
char **get_map(t_struct *utils);
int get_piece(t_struct *utils);
char **make_heatmap(t_struct *u, int num, int xx, int yy);

#endif
