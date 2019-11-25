#include "filler.h"

/*
** il faut trouver un moyen d adapter ca en fonction des strategies
*/

int		check_piece_values(t_struct *u, int x_place, int y_place)
{
	int i;
	int x;
	int y;
	int check;

	i = -1;
	check = 0;
	while (++i < u->piece.total)
	{
		if (((y_place + u->piece.coord[i][1] < 0 || y_place + u->piece.coord[i][1] >= u->map_h)
				|| (x_place + u->piece.coord[i][0] < 0 || x_place + u->piece.coord[i][0] >= u->map_w)))
			return (0);
		if (u->map[y_place + u->piece.coord[i][1]][x_place + u->piece.coord[i][0]] &&
				(is_me(u, u->map[y_place + u->piece.coord[i][1]][x_place + u->piece.coord[i][0]]))
				&& ((y_place + u->piece.coord[i][1] >= 0 && y_place + u->piece.coord[i][1] < u->map_h)
				&& (x_place + u->piece.coord[i][0] >= 0 && x_place + u->piece.coord[i][0] < u->map_w)))
			check++;
		if ((y_place + u->piece.coord[i][1] >= 0 && y_place + u->piece.coord[i][1] < u->map_h)
				&& (x_place + u->piece.coord[i][0] >= 0 && x_place + u->piece.coord[i][0] < u->map_w) &&
			(is_enemy(u, u->map[y_place + u->piece.coord[i][1]][x_place + u->piece.coord[i][0]]) ||
			u->map[y_place + u->piece.coord[i][1]][x_place + u->piece.coord[i][0]] == 'A' ||
			u->map[y_place + u->piece.coord[i][1]][x_place + u->piece.coord[i][0]] == 'a'))
			return (0);
	}
	if (check != 1)
		return (0);
	return (1);

}

int 	check_possibilities(t_struct *u, int x_map, int y_map)
{
	int x;
	int y;
	int cnt;

	cnt = 0;
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
*/

int 	check_if_match(t_struct *u, int x_map, int y_map)
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

int		update_y(t_struct *u, int y)
{
	int x;

	while (y < u->map_h)
	{
		x = -1;
		while (++x < u->map_w)
			if (u->map[y][x] == '.')
				return (y);
		y++;
	}
	if (y - u->piece.h >= 0)
		return (y - u->piece.h);
	return (0);
}

int		other_place(t_struct *u)
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
