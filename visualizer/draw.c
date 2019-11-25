/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 10:25:17 by skrabby           #+#    #+#             */
/*   Updated: 2019/11/15 10:47:26 by skrabby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

int			g_size = 170;

void		put_mapsquare(t_vis *v, t_drawmap *dp, t_vm *map)
{
	if (map->arr[dp->y][dp->x] == '.')
	{
		change_color(0, 12, 25, v);
		draw_square(v->width / ((v->width) / g_size) +
		dp->tmpx + dp->padding_x, v->height / (v->height / g_size) +
		dp->tmpy + dp->padding_y, dp->sqlen, v);
	}
	else if (map->arr[dp->y][dp->x] == 'o' ||
	map->arr[dp->y][dp->x] == 'O')
	{
		v->p1score++;
		change_color(255, 128, 255, v);
		draw_square(v->width / ((v->width) / g_size) +
		dp->tmpx + dp->padding_x, v->height / (v->height / g_size) +
		dp->tmpy + dp->padding_y, dp->sqlen, v);
	}
	else if (map->arr[dp->y][dp->x] == 'x' ||
	map->arr[dp->y][dp->x] == 'X')
	{
		v->p2score++;
		change_color(128, 255, 255, v);
		draw_square(v->width / ((v->width) / g_size) +
		dp->tmpx + dp->padding_x, v->height / (v->height / g_size) +
		dp->tmpy + dp->padding_y, dp->sqlen, v);
	}
}

void		draw_rectangle(int start_x, int start_y, t_vis *v)
{
	int		x;
	int		y;
	int		t;

	y = 0;
	t = 0;
	while (y < (v->h * 4))
	{
		x = 0;
		while (x < (v->len * 4))
		{
			v->ret[x + t +
			((start_y * v->width * 4) + (start_x * 4))] = v->blue;
			v->ret[x + t + 1 +
			((start_y * v->width * 4) + (start_x * 4))] = v->green;
			v->ret[x + t + 2 +
			((start_y * v->width * 4) + (start_x * 4))] = v->red;
			v->ret[x + t + 3 +
			((start_y * v->width * 4) + (start_x * 4))] = 0;
			x += 4;
		}
		y += 4;
		t += (v->width * 4);
	}
}

void		draw_square(int start_x, int start_y, int size, t_vis *v)
{
	int		i;
	int		i2;
	int		tmp;

	i2 = 0;
	tmp = 0;
	while (i2 < (size * 4))
	{
		i = 0;
		while (i < (size * 4))
		{
			v->ret[i + tmp + ((start_y * v->width * 4) +
					(start_x * 4))] = v->blue;
			v->ret[i + tmp + 1 + ((start_y * v->width * 4) +
					(start_x * 4))] = v->green;
			v->ret[i + tmp + 2 + ((start_y * v->width * 4) +
					(start_x * 4))] = v->red;
			v->ret[i + tmp + 3 + ((start_y * v->width * 4) +
					(start_x * 4))] = 0;
			i += 4;
		}
		i2 += 4;
		tmp += (v->width * 4);
	}
}

void		draw_pcolor(t_vis *v, t_vm *map)
{
	v->h = v->height - ((v->height / (v->height / g_size)) * 2);
	v->len = v->width - ((v->width / ((v->width) / g_size)) * 2);
	change_color(255, 128, 255, v);
	draw_square((v->width / 2) - 60, (v->height / 10) - 20, 20, v);
	change_color(128, 255, 255, v);
	draw_square((v->width / 2) - 60, (v->height - v->height / 10), 20, v);
}

void		draw_background(t_vis *v)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	change_color(10, 20, 35, v);
	while (i < (v->height * v->width * 4))
	{
		(v->ret)[i] = v->blue;
		(v->ret)[i + 1] = v->green;
		(v->ret)[i + 2] = v->red;
		(v->ret)[i + 3] = 0;
		i += 4;
		if (count < 22000)
			count++;
		else if (count == 22000 && v->blue <= 255)
		{
			count = 0;
			v->blue++;
		}
	}
}
