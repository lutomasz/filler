/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_place.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:46:26 by lutomasz          #+#    #+#             */
/*   Updated: 2019/11/27 14:46:29 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**	x_p = current x on the map
**	y_p = current y on the map
**	i for iteration through the pieces coords
**	1) if * of the piece is out of bounds
**		return FALSE == not a valid position
**	2) if position of * is valid && touch my token + !out_of_bounds, marker +1
**	3) if !out_of_bounds but touches an enemy (his_c || 'a' || 'A')
**		return FALSE == not a valid position
**	il faut trouver un moyen d adapter ca en fonction des strategies
*/

static int		check_piece_values(t_struct *u, int x_p, int y_p)
{
	int i;
	int check;

	i = -1;
	check = 0;
	while (++i < u->piece.total)
	{
		if (((y_p + u->piece.coord[i][1] < 0 || y_p + u->piece.coord[i][1] >=
			u->map_h) || (x_p + u->piece.coord[i][0] < 0
			|| x_p + u->piece.coord[i][0] >= u->map_w)) ||
			(is_enemy(u, u->map[y_p + u->piece.coord[i][1]][x_p +
			u->piece.coord[i][0]]) || u->map[y_p + u->piece.coord[i][1]][x_p +
			u->piece.coord[i][0]] == 'A' || u->map[y_p +
			u->piece.coord[i][1]][x_p + u->piece.coord[i][0]] == 'a'))
			return (0);
		if (u->map[y_p + u->piece.coord[i][1]][x_p + u->piece.coord[i][0]] &&
			(is_me(u, u->map[y_p + u->piece.coord[i][1]][x_p +
			u->piece.coord[i][0]])))
			check++;
	}
	if (check != 1)
		return (0);
	return (1);
}

/*
**	creates a square round the current map position to check if there is
**	space on adjascent values.
*/

static int		check_possibilities(t_struct *u, int x_map, int y_map)
{
	int x;
	int y;

	y = y_map - 1;
	while (y <= (y_map + 1) && y < u->map_h)
	{
		x = x_map - 1;
		while (x <= (x_map + 1))
		{
			if ((y >= 0 && x >= 0) && (y < u->map_h && x < u->map_w)
					&& (u->map[y][x] == ',' || u->map[y][x] == '.'))
			{
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

/*
**	y_place_start && x_place_start need -1 but it s directly added in the loop
**	start places are set depending on the size of the piece we got.
**	if check_possibilities is 1, it may be possible to place and it s
**	worth to check if it exists a valid solution
**	if solution, set its coords
*/

static int		check_if_match(t_struct *u, int x_map, int y_map)
{
	int x_place_start;
	int y_place_start;

	y_place_start = y_map - (u->piece.h);
	while (++y_place_start < (y_map + u->piece.h))
	{
		x_place_start = x_map - (u->piece.w);
		while (++x_place_start < (x_map + u->piece.w))
		{
			if (check_possibilities(u, x_map, y_map) == 1)
			{
				if (check_piece_values(u, x_place_start, y_place_start) == 1)
				{
					u->sol_x = x_place_start;
					u->sol_y = y_place_start;
					return (1);
				}
			}
		}
	}
	return (0);
}

/*
**	pick the first my_c on the map to set the y to avoid pointless checks
**	if token on map is mine, check for possible solution
**	if I got a valid solution
**		return TRUE
**	else FALSE
*/

int				other_place(t_struct *u)
{
	int x;
	int y;

	y = (u->my_c[0] == 'o') ? u->first_o.y : u->first_x.y;
	while (y < u->map_h)
	{
		x = -1;
		while (++x < u->map_w)
			if (is_me(u, u->map[y][x]))
				if (check_if_match(u, x, y) == 1)
					return (1);
		y++;
	}
	return (0);
}
