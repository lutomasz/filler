/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 20:06:29 by lutomasz          #+#    #+#             */
/*   Updated: 2019/03/11 20:06:32 by lutomasz         ###   ########.fr       */
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
	
}				t_piece;

typedef struct 	s_struct
{
	//gestion map;
	int map_x;
	int map_y;
	int fd;
	char **tmp_map;
	
	//gestion situation 
	bool first_x_on;
	bool first_o_on;
	bool last_played_x_on;
	bool last_played_o_on;

	char **shape;
	char **tmp_shape;
	
	t_piece 	piece;
	t_shift		shift;
	t_first_o 	first_o;
	t_first_x 	first_x;
	t_last_played_x last_played_x;
	t_last_played_o last_played_o;
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

t_struct *init_utils(void);
void ft_get_size_map(t_struct *utils);
char **get_tmp_map(t_struct *utils);
void get_piece(t_struct *utils);


#endif
