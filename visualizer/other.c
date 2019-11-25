/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 10:39:16 by skrabby           #+#    #+#             */
/*   Updated: 2019/11/15 10:40:56 by skrabby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void		set_var(t_vis *v, t_vm *map)
{
	v->red = 0;
	v->green = 0;
	v->blue = 0;
	v->p1score = 0;
	v->p2score = 0;
	v->game_over = 0;
	v->map_created = 0;
	v->first_parse = 1;
	map->setwh = 0;
}

int			keyboard(int button, t_vis *v, t_vm *map)
{
	int		i;
	int		j;

	i = 1;
	if (button == ESC)
		exit(1);
	return (0);
}

void		set_height_width(t_vis *v, t_vm *map)
{
	int tmpy;
	int tmpx;

	v->height = map->sizey;
	v->width = map->sizex;
	tmpy = v->height;
	tmpx = v->width;
	while ((v->height < 1000 && v->width < 2000) ||
			(v->height < 700 || v->width < 700))
	{
		v->height += tmpy;
		v->width += tmpx;
	}
	map->setwh = 1;
}
