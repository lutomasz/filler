/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 10:31:11 by skrabby           #+#    #+#             */
/*   Updated: 2019/11/15 10:46:04 by skrabby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void		change_color(int r, int g, int b, t_vis *v)
{
	v->red = r;
	v->green = g;
	v->blue = b;
}

static void	set_mvar(t_vis *v, t_drawmap *dp, t_vm *map)
{
	dp->gap = 1;
	v->p1score = 0;
	v->p2score = 0;
	dp->padding_x = 0;
	dp->padding_y = 0;
	dp->y = 0;
	dp->x = 0;
	dp->tmpx = 0;
	dp->tmpy = 0;
	dp->sqlen = (v->h - ((map->sizey + dp->gap) * dp->gap)) / (map->sizey);
	dp->padding_y = (v->h - (dp->sqlen * map->sizey) -
	((map->sizey - dp->gap) * dp->gap)) / 2;
	dp->padding_x = (v->len - (dp->sqlen * map->sizex) -
	((map->sizex - dp->gap) * dp->gap)) / 2;
}

void		draw_map(t_vis *v, t_vm *map)
{
	t_drawmap *dp;

	if (!(dp = (t_drawmap*)malloc(sizeof(t_drawmap))))
		exit(0);
	set_mvar(v, dp, map);
	while (dp->y < map->sizey)
	{
		while (dp->x < map->sizex)
		{
			put_mapsquare(v, dp, map);
			dp->tmpx += dp->sqlen + dp->gap;
			dp->x++;
		}
		dp->y++;
		dp->tmpx = 0;
		dp->tmpy += dp->sqlen + dp->gap;
		dp->x = 0;
	}
	free(dp);
}

void		draw_gameover(t_vis *v)
{
	char *s;
	char *s2;

	if (v->game_over)
	{
		s = "<WINNER WINNER";
		s2 = "CHICKEN DINNER>";
		if (v->p1score > v->p2score)
		{
			mlx_string_put(v->mlx, v->win, (v->width / 2) - 275,
			(v->height / 10) + 20, 0x0FFFFFF, s);
			mlx_string_put(v->mlx, v->win, (v->width / 2) + 133,
			(v->height / 10) + 20, 0x0FFFFFF, s2);
		}
		else if (v->p2score > v->p1score)
		{
			mlx_string_put(v->mlx, v->win, (v->width / 2) - 275,
			v->height - (v->height / 10) - 40, 0x0FFFFFF, s);
			mlx_string_put(v->mlx, v->win, (v->width / 2) + 133,
			v->height - (v->height / 10) - 40, 0x0FFFFFF, s2);
		}
		else if (v->p2score == v->p1score)
			mlx_string_put(v->mlx, v->win, (v->width / 2) - 60,
			v->height / 2 - 20, 0x0FFFFFF, "WTF!!! DRAW???");
	}
}

void		draw_bars(t_vis *v, t_vm *map)
{
	int size;

	size = 110;
	v->h = 20;
	v->len = size * 2;
	change_color(45, 60, 95, v);
	draw_rectangle((v->width / 2) - size, (v->height / 10) + 20, v);
	draw_rectangle((v->width / 2) - size, v->height - (v->height / 10) - 40, v);
	change_color(0, 255, 125, v);
	v->len = v->p1score * size * 2 / (map->sizex * map->sizey);
	draw_rectangle((v->width / 2) - size, (v->height / 10) + 20, v);
	v->len = v->p2score * size * 2 / (map->sizex * map->sizey);
	draw_rectangle((v->width / 2) - size, v->height - (v->height / 10) - 40, v);
}
