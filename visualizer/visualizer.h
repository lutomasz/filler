/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 04:16:36 by skrabby           #+#    #+#             */
/*   Updated: 2019/11/15 10:40:40 by skrabby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H
# define ESC 53
# define WINDOW_NAME "Filler: God's battle"

# include "minilibx/mlx.h"
# include "../filler.h"

typedef struct		s_vis
{
	int				height;
	int				width;
	void			*mlx;
	void			*win;
	void			*img;
	char			*ret;
	int				endian;
	int				size_line;
	int				bits_per_pixel;
	int				red;
	int				green;
	int				blue;
	int				len;
	int				h;
	int				p1score;
	int				p2score;
	int				game_over;
	int				map_created;
	int				first_parse;
}					t_vis;

typedef struct		s_vm
{
	int				sizex;
	int				sizey;
	int				setwh;
	int				count_p1;
	int				count_p2;
	char			*p1_name;
	char			*p2_name;
	char			**arr;
}					t_vm;

typedef struct		s_drawmap
{
	int				y;
	int				x;
	int				tmpx;
	int				tmpy;
	int				sqlen;
	int				gap;
	int				padding_x;
	int				padding_y;
}					t_drawmap;

void				draw_background(t_vis *v);
void				draw_pcolor(t_vis *v, t_vm *map);
void				draw_square(int start_x, int start_y, int size, t_vis *v);
void				draw_rectangle(int start_x, int start_y, t_vis *v);
void				draw_bars(t_vis *v, t_vm *map);
void				draw_gameover(t_vis *v);
void				draw_map(t_vis *v, t_vm *map);
void				put_mapsquare(t_vis *v, t_drawmap *dp, t_vm *map);
void				change_color(int r, int g, int b, t_vis *v);
void				parse_data(t_vis *v, t_vm *map);
void				check_players(char *line, t_vm *map, int player);
void				set_height_width(t_vis *v, t_vm *map);
void				free_vmap(t_vis *v, t_vm *map);
void				set_var(t_vis *v, t_vm *map);
int					keyboard(int button, t_vis *v, t_vm *map);

#endif
