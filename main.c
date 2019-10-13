/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <lutomasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 20:04:39 by lutomasz          #+#    #+#             */
/*   Updated: 2019/10/13 18:33:30 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int test(int i)
{
	return (i*i);
}

// int can_place(t_struct *u, int x, int y)
// {
// 	int xx;
// 	int yy;
// }

int is_enemy(char c)
{
	if (c == 'o' || c == 'O')
		return (1);
	return (0);
}

// void place_random(t_struct *u)
// {
// 	int i;
// 	int j;
// 	int is_placed;
// 	int do_place;
//
// 	is_placed = 0;
// 	while (!is_placed)
// 	{
// 		i = -1;
// 		while (++i < u->map_h)
// 		{
// 			j = -1;
// 			while(++j < u->map_w)
// 			{
// 				if ((u->tmp_map[i][j] == u->symbol || u->tmp_map[i][j] == u->symbol + 32) && can_place(u, j, i) && rand() * 10 < 3)
// 				{
// 					rand() * 10;
// 				}
// 			}
// 		}
// 	}
// }

int no_dots(t_struct *u)
{
	int i;
	int j;

	i = -1;
	while (++i < u->map_h)
	{
		j = -1;
		while (++j < u->map_w)
			if (u->tmp_map[i][j] == '.')
				return (0);
	}
	return (1);
}

void update_adj_nbrs(t_struct *u, int num, int xx, int yy)
{
	int i;
	int j;

	i = -2;
	while (++i < 2)
	{
		if (yy + i > 0 && yy + i < u->map_h)
		{
			j = -2;
			while (++j < 2)
			{
				if (i == 0 && j == 0)
				{
					u->tmp_map[yy][xx] = 'A';
					++j;
				}
				if (xx + j > 0 && xx + j < u->map_w)
				{
					if ((u->tmp_map[yy + i][xx + j] == '.' || u->tmp_map[yy + i][xx + j] - 48 > num) && u->tmp_map[yy + i][xx + j] != 'o' && u->tmp_map[yy + i][xx + j] != 'O' && u->tmp_map[yy + i][xx + j] != 'A' && u->tmp_map[yy + i][xx + j] != 'a')
						u->tmp_map[yy + i][xx + j] = num + 48;
					if (is_enemy(u->tmp_map[yy + i][xx + j]))
					{
						u->tmp_map[yy + i][xx + j] = 'a';
						make_heatmap(u, 0, xx + j, yy + i);
					}
				}
			}
		}
	}
}

char **make_heatmap(t_struct *u, int num, int xx, int yy)
{
	int x;
	int y;

//	if (no_dots(u))
//		return (u->tmp_map);
	x = (u->c == 'o') ? u->first_o.x : u->last_played_o.x;
	y = (u->c == 'o') ? u->first_o.y : u->last_played_o.y;
	x = (xx >= 0) ? xx : x;
	y = (xx >= 0) ? yy : y;
	update_adj_nbrs(u, num + 1, x, y);
	return (u->tmp_map);
}

char **get_heatmap(t_struct *u)
{
	if (u->first_o.x < 0) // first round
	{
		u->c = '0';
		return(make_heatmap(u, 0, -1, -1));
	}
	else
	{
		u->c = 'o';
		return(make_heatmap(u, 0, -1, -1));
	}
}

void place_piece(t_struct *u)
{

}

int main(int argc, char **argv)
{
	t_struct *u;
	int x;
	int y;

	u = init_utils();
	ft_get_size_map(u);  //read only once
	printf("sadasasd\n");
	u->tmp_map = get_tmp_map(u);
	u->symbol = 'x';  // X = x + 32
	get_piece(u);

	u->tmp_map = get_heatmap(u);

	//ft_filler(u);
	ft_print_tab2(u->tmp_map);

	// printf("%s\n", "MAP");
	// printf("map_w == %d\n", u->map_w);
	// printf("map_h == %d\n", u->map_h);
	// printf("%s\n", "MATRIX");
	// printf("first_x_on == %d\n", u->first_x_on);
	// printf("first_o_on == %d\n", u->first_o_on);
	// printf("first_o.x == %d\n", u->first_o.x);
	// printf("first_o.y == %d\n", u->first_o.y);
	// printf("first_x.x == %d\n", u->first_x.x);
	// printf("first_x.y == %d\n", u->first_x.y);
	// printf("last_played_x_on == %d\n", u->last_played_x_on);
	// printf("last_played_o_on == %d\n", u->last_played_o_on);
	// printf("last_played_x.x == %d\n", u->last_played_x.x);
	// printf("last_played_x.y == %d\n", u->last_played_x.y);
	// printf("last_played_o.x == %d\n", u->last_played_o.x);
	// printf("last_played_o.y == %d\n", u->last_played_o.y);
	// printf("%s\n", "PIECE");
	// ft_print_tab2(u->tmp_shape);
	// printf("%s\n", "SHAPE");
	// if (u->piece.total > 0)
	// 	ft_print_tab2(u->shape);
	// printf("shift.left == %d\n", u->shift.left);
	// printf("shift.up == %d\n", u->shift.up);
	// printf("down_shift == %d\n", u->shift.down);
	// printf("right_shift == %d\n", u->shift.right);
	// printf("\n");
	// printf("piece_h == %d\n", u->piece.h);
	// printf("piece_w == %d\n", u->piece.w);
	// printf("piece.first_x == %d\n", u->piece.first_x);
	// printf("piece.first_y == %d\n", u->piece.first_y);
	// printf("piece.last_x == %d\n", u->piece.last_x);
	// printf("piece.last_y == %d\n", u->piece.last_y);
	// printf("piece.total == %d\n", u->piece.total);
	// printf("\n");
	// printf("coord\n");
	// x = 0;
	// while (x < u->piece.total)
	// {
	// 	y = 0;
	// 	while (y < 2)
	// 	{
	// 		printf("%d", u->coord[x][y]);
	// 		y++;
	// 	}
	// 	printf("\n");
	// 	x++;
	// }

	//ft_filler(u);
}
