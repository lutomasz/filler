#include "filler.h"

// typedef struct s_first_x
// {
// 	int x;
// 	int y;
// }				t_first_x;

// typedef struct s_first_o
// {
// 	int x;
// 	int y;
// }	

// typedef struct s_piece
// {
// 	int h;
// 	int w;
// 	int first_x;
// 	int first_y;
// 	int last_x;
// 	int last_y;
// 	int total;
// 	int	**coord;
// 	int up;
// 	int left;
// 	int down;
// 	int right;
// }	

// Piece 4 4:
// ....
// ....
// ...*
// ..**

//u->piece.coord[i][0];
//u->piece.coord[i][1];
//u->my_c[0] = (u->player1) ? 'o' : 'x';

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
		if (u->map[y_place + u->piece.coord[i][1]][x_place + u->piece.coord[i][0]] &&
				(is_me(u, u->map[y_place + u->piece.coord[i][1]][x_place + u->piece.coord[i][0]]))
				&& ((y_place + u->piece.coord[i][1] >= 0 && y_place + u->piece.coord[i][1] < u->map_h)
				&& (x_place + u->piece.coord[i][0] >= 0 && x_place + u->piece.coord[i][0] < u->map_w)))
		{
			// u->x_sol = x_place + u->piece.coord[i][0];
			// u->y_sol = y_place + u->piece.coord[i][1];
			check++;
		}
		// printf("CHECK = %d\n", y_place + u->piece.coord[i][1]);
		// printf("CHECK = %d\n", x_place + u->piece.coord[i][0]);
		if (((y_place + u->piece.coord[i][1] < 0 || y_place + u->piece.coord[i][1] >= u->map_h)
				|| (x_place + u->piece.coord[i][0] < 0 || x_place + u->piece.coord[i][0] >= u->map_w)))
		{
			//printf("COORD NEG\n");
			return (0);
		}	

		//printf("here3\n");
		//printf("map char = %c\n", u->map[y_place + u->piece.coord[i][1]][x_place + u->piece.coord[i][0]]);
		if ((y_place + u->piece.coord[i][1] >= 0 && y_place + u->piece.coord[i][1] < u->map_h)
				&& (x_place + u->piece.coord[i][0] >= 0 && x_place + u->piece.coord[i][0] < u->map_w) &&
			(is_enemy(u, u->map[y_place + u->piece.coord[i][1]][x_place + u->piece.coord[i][0]]) ||
			u->map[y_place + u->piece.coord[i][1]][x_place + u->piece.coord[i][0]] == 'A' ||
			u->map[y_place + u->piece.coord[i][1]][x_place + u->piece.coord[i][0]] == 'a'))
		{
			//printf("ENEMY SPOTEDT\n");
			return (0);
		}
		//printf("map char = %c\n", u->map[y_place + u->piece.coord[i][1]][x_place + u->piece.coord[i][0]]);
	}
	//printf("xXXXX %d\n", x_place + u->piece.coord[0][0]);
	//printf("yYYYY %d\n", y_place + u->piece.coord[0][1]);
	// printf("CHECK +++++ == %d\n", check);
	if (check != 1)
		return (0);
	return (1);

}

int 	check_if_match(t_struct *u, int x_map, int y_map)
{
	int cnt;
	int i;
	int x_place_start;
	int y_place_start;
	int ret;
	// int x_place_end;
	// int y_place_end;

	ret = 0;
	cnt = 0;
	i = -1;
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
				u->x_sol = x_place_start;
				u->y_sol = y_place_start;
				return (1);
			}	
			// printf("ret = %d\n", ret);
			// cnt++;
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
	ft_putnbr(u->y_sol);
	ft_putchar(' ');
	ft_putnbr(u->x_sol);
	ft_putchar('\n');
}

int		other_place(t_struct *u)
{

	//u->my_c[0] = (u->player1) ? 'o' : 'x';
	int x;
	int y;

	//printf("%c\n", u->my_c[0]);
	//x = (u->my_c[0] == 'o') ? u->first_o.x : u->first_x.x;
	y = (u->my_c[0] == 'o') ? u->first_o.y : u->first_x.y;
	printf("here\n");
	while (y < u->map_h)
	{
		//printf("INFINITE Y\n");
		x = (u->my_c[0] == 'o') ? u->first_o.x : u->first_x.x;
		while (x < u->map_w)
		{

			//printf("here\n");
			if (check_if_match(u, x, y) == 1)
			{
				print_solution(u);
				return (1);
			}
			x++;
		}
		y++;
	}
	// printf("x et y = %d %d\n", x, y);
	// printf("up = %d\n", u->shift.up);
	// printf("left = %d\n", u->shift.left);
	// printf("h = %d\n", u->piece.h);
	// printf("w = %d\n", u->piece.w);
	return (0);
}