#include "filler.h"

//il faut trouver un moyen d adapter ca en fonction des strategies

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

int 	check_if_match(t_struct *u, int x_map, int y_map)
{
	int x_place_start;
	int y_place_start;
	// int x_place_end;
	// int y_place_end;

	//ft_print_tab2(u->map);

	y_place_start = y_map - (u->piece.h); // -1 but added in while
	while (++y_place_start < (y_map + u->piece.h))
	{
		x_place_start = x_map - (u->piece.w); // -1 but added in while
		while (++x_place_start < (x_map + u->piece.w))
		{
			//printf("here2\n");
			// printf("x_place_start = %d\n", x_place_start);
			// printf("y_place_start = %d\n", y_place_start);
			if (check_piece_values(u, x_place_start, y_place_start) == 1)
			{

				//printf("ok\n");
				u->sol_x = x_place_start;
				u->sol_y = y_place_start;
				return (1);
			}
		}
		//printf("CNT = %d\n", cnt);
	}
	return (0);


	// while (++i < u->piece.total)
	// {

	// }
}

void	print_solution(t_struct *u)
{
	ft_putnbr(u->sol_y);
	ft_putchar(' ');
	ft_putnbr(u->sol_y);
	ft_putchar('\n');
}

int		check_free_spaces(t_struct *u)
{
	int i;
	int j;

	i = -1;

	while (++i < u->map_h / 2)
	{
		j = -1;
		//printf("n1 (%d)\n", i);
		while (++j < u->map_w)
		{
		//	printf("n2 (%d)\n", j);
			//printf("map_val: %d\n", u->map[i][j]);
			if (u->map[i][j] == '.')
			{
			//	printf("n3\n");
				return (0);
			}
		}
	}
	return (1);
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
