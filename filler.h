/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <lutomasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 20:06:29 by lutomasz          #+#    #+#             */
/*   Updated: 2019/11/20 16:32:00 by spozzi           ###   ########.fr       */
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
#include <time.h>

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
	int	**coord;
	int up;
	int left;
	int down;
	int right;
}				t_piece;

typedef struct 	s_struct
{
	//gestion map;
	int				map_w;
	int				map_h;
	int				fd;
	char			**map;
	char			symbol;
	char			c;
	char			my_c[2];
	char			his_c[2]; //0 -> o 1 -> O
	int				best_pos;
	//gestion situation
	bool			first_x_on;
	bool			first_o_on;
	bool			last_played_x_on;
	bool			last_played_o_on;

	int 			x_sol;
	int 			y_sol;

	int 			player1 : 3;
	char			*en;
	char			*me;

	char			**shape;
	char			**tmp_shape;
	int				**h_map;

	//int				possible_pos[9000][3];
	int				**possible_pos;
	int				num_me;
	int				min_dist_adj;
	int				**trimmed_pos;
	int				curr_piece_fulcrum;
	int				*smallest_val;
	int				num_of_trims;
	int				x;
	int				y;
	int				origin_x;
	int				origin_y;
	int				i;
	int				sol_x;
	int				sol_y;
	int				placed_one;

	t_piece 		piece;
	t_shift			shift;
	t_first_o 		first_o;
	t_first_x 		first_x;
	t_last_played_x last_played_x;
	t_last_played_o last_played_o;
	t_first_o		first_en;
	t_first_o		last_played_en;
}				t_struct;

int			init_utils(t_struct *u, char *map);
int			ft_get_size_map(t_struct *utils, int *i);
int			get_map(t_struct *utils);
int			get_piece(t_struct *utils);
char		**make_heatmap(t_struct *u, int num, int xx, int yy);
void		set_me_his(t_struct *u);
char		**get_heatmap(t_struct *u);
void		set_players_pos(t_struct *u);
int			is_enemy(t_struct *u, char c);
int			is_me(t_struct *u, char c);
int			no_dots(t_struct *u);
void		update_adj_nbrs(t_struct *u, int num, int x, int y);
void		select_pos(t_struct *u);
int			place_all_poss(t_struct *u, int solutions[u->piece.total][2]);
void		usage(void);
void		analyse_tab(char **tab, t_struct *u);
char		*copy_line(char *str);
void		place_piece(t_struct *u);
void		free_unset_tab(char **str, int cnt);
void		free_str2(char **str);
void		free_double_int(int **str, int elements);
int			other_place(t_struct *u);



#endif
