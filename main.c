/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <lutomasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 20:04:39 by lutomasz          #+#    #+#             */
/*   Updated: 2019/10/17 16:43:52 by spozzi           ###   ########.fr       */
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

int is_enemy(t_struct *u, char c)
{
	if (c == u->his_c[0] || c == u->his_c[1])
		return (1);
	return (0);
}

int is_me(t_struct *u, char c)
{
	if (c == u->my_c[0] || c == u->my_c[1])
	return (1);
	return (0);
}

int is_enemyA(t_struct *u, char c)
{
	if (is_me(u, c))
		return (1);
	if (is_enemy(u, c) || c == 'A')
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
// 				if ((u->map[i][j] == u->symbol || u->map[i][j] == u->symbol + 32) && can_place(u, j, i) && rand() * 10 < 3)
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
			if (u->map[i][j] == '.')
				return (0);
	}
	return (1);
}

void update_adj_nbrs(t_struct *u, int num, int x, int y)
{
	int i;
	int j;

	i = -2;
//	if (is_enemy(u->map[yy][xx]))
		u->map[y][x] = 'A';
	while (++i < 2)
	{
		if (y + i >= 0 && y + i < u->map_h)
		{
			j = -2;
			while (++j < 2)
			{
				if (i == 0 && j == 0)
					++j;
				if (x + j >= 0 && x + j < u->map_w)
				{
					if ((u->map[y + i][x + j] == '.' || u->map[y + i][x + j]
							- 48 > num) && !is_enemyA(u, u->map[y + i][x + j]))
						u->map[y + i][x + j] = num + 48;
					if (is_enemy(u, u->map[y + i][x + j]))
						make_heatmap(u, 1, x + j, y + i);
				}
			}
		}
	}
}

void put_adj_nbrs(t_struct *u, int num, int x, int y)
{
	int i;
	int j;

	i = -2;
	while (++i < 2)
	{
		if (y + i >= 0 && y + i < u->map_h)
		{
			j = -2;
			while (++j < 2)
				if ((u->map[y + i][x + j] - 48 > num
						|| u->map[y + i][x + j] == '.')
						&& !is_enemyA(u, u->map[y + i][x + j]))
					u->map[y + i][x + j] = num + 48 + 1;
		}
	}
}

char **make_heatmap(t_struct *u, int num, int xx, int yy)
{
	int x;
	int y;

<<<<<<< HEAD
	x = (u->c == u->his_c[1]) ? u->first_o.x : u->last_played_o.x;
	y = (u->c == u->his_c[1]) ? u->first_o.y : u->last_played_o.y;
=======
	x = (u->c == 'O') ? u->first_o.x : u->last_played_o.x;
	y = (u->c == 'O') ? u->first_o.y : u->last_played_o.y;
	//printf("%d %d\n", x, y);
	x = (xx >= 0) ? xx : x;
	y = (xx >= 0) ? yy : y;
	//printf("%d %d\n", x, y);
	update_adj_nbrs(u, num + 1, x, y);
>>>>>>> 8ab825297f814a0ee51a421656375cb3d1bb34ea
	x = (xx >= 0) ? xx : x;
	y = (xx >= 0) ? yy : y;
	update_adj_nbrs(u, 1, x, y);
	num = 1;
	while(!no_dots(u))
	{
		y = -1;
		while (++y < u->map_h)
		{
			x = -1;
			while (++x < u->map_w)
			{
				if (u->map[y][x] - 48 == num)
					put_adj_nbrs(u, num, x, y);
			}
		}
		++num;
	}
	return (u->map);
}

char **get_heatmap(t_struct *u)
{
	if (u->last_played_o.x < 0) // first round
	{
		u->c = u->his_c[1];
		return(make_heatmap(u, 0, -1, -1));
	}
	else
	{
		u->c = u->his_c[0];
		return(make_heatmap(u, 0, -1, -1));
	}
}

void place_piece(t_struct *u)
{

}

<<<<<<< HEAD
void set_me_his(t_struct *u)
{
	u->his_c[0] = 'x';
	u->his_c[1] = 'X';
	u->my_c[0] = 'o';
	u->my_c[1] = 'O';
=======
void	update_heatmap(t_struct *u)
{
	int i;
	int j;

	i = -1;
	while (u->map_cpy[++i])
	{
		j = -1;
		while (u->map_cpy[i][++j])
		{
			// u->map[i][j] = (u->map_cpy[i][j] = 'X') ? (u->map[i][j] = 'X') : u->map[i][j];
			// u->map[i][j] = (u->map_cpy[i][j] = 'x') ? (u->map[i][j] = 'x') : u->map[i][j];
			// u->map[i][j] = (u->map_cpy[i][j] = 'o') ? (u->map[i][j] = 'o') : u->map[i][j];
			// u->map[i][j] = (u->map_cpy[i][j] = 'O') ? (u->map[i][j] = 'O') : u->map[i][j];
			if (u->map_cpy[i][j] == 'X')
				u->map[i][j] = 'X';
			if (u->map_cpy[i][j] == 'x')
				u->map[i][j] = 'x';
			if (u->map_cpy[i][j] == 'O')
				u->map[i][j] = 'O';
			if (u->map_cpy[i][j] == 'o')
				u->map[i][j] = 'o';
		}
		//free cpy
	}

>>>>>>> 8ab825297f814a0ee51a421656375cb3d1bb34ea
}

int main(int argc, char **argv)
{
	t_struct *u;
	// int x;
	// int y;
	int **tab;

	if (!(u = init_utils(argv[1])))
		return (-1);
	if ((ft_get_size_map(u)) == -1)
		return (-1); //print error //read only once
	u->map = get_map(u);
	set_me_his(u);
	get_piece(u);
<<<<<<< HEAD
	//printf("ok\n");
	ft_print_tab2(u->map);
	printf("\n");
	if (u->first_x_on == 1 && u->first_o_on)
=======
	ft_print_tab2(u->map);
	if (u->first_x_on == 1 || u->first_o_on == 1)
>>>>>>> 8ab825297f814a0ee51a421656375cb3d1bb34ea
		u->map = get_heatmap(u);
	update_heatmap(u);
	ft_print_tab2(u->map);
	// printf("%s\n", "MAP");
	// printf("map_w == %d\n", u->map_w);
	// printf("map_h == %d\n", u->map_h);
<<<<<<< HEAD
	u->map = get_heatmap(u);
	ft_print_tab2(u->map);
=======
	// ft_print_tab2(u->map);
>>>>>>> 8ab825297f814a0ee51a421656375cb3d1bb34ea

	// printf("%s\n", "MAP");
	//printf("map_w == %d\n", u->map_w);
	//printf("map_h == %d\n", u->map_h);
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
<<<<<<< HEAD
	printf("\n%s\n", "PIECE");
	ft_print_tab2(u->tmp_shape);
=======
	// printf("%s\n", "PIECE");
	// ft_print_tab2(u->tmp_shape);
>>>>>>> 8ab825297f814a0ee51a421656375cb3d1bb34ea
	// tab = atoi_tab2(u->map, u->map_w, u->map_h);
	// print_int2(tab, u->map_w, u->map_h);
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
	//print_int2(u->coord, u->piece.total, 2);
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
