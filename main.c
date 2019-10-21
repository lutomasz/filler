/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <lutomasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 20:04:39 by lutomasz          #+#    #+#             */
/*   Updated: 2019/10/21 17:26:12 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		test(int i)
{
	return (i*i);
}

// int can_place(t_struct *u, int x, int y)
// {
// 	int xx;
// 	int yy;
// }

int		is_enemy(t_struct *u, char c)
{
	if (c == u->his_c[0] || c == u->his_c[1])
		return (1);
	return (0);
}

int		is_me(t_struct *u, char c)
{
	if (c == u->my_c[0] || c == u->my_c[1])
		return (1);
	return (0);
}

int		is_enemyA(t_struct *u, char c)
{
	if (is_me(u, c))
		return (1);
	if (is_enemy(u, c) || c == 'A')
		return (1);
	return (0);
}

int		no_dots(t_struct *u)
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

int		find_smallest_val(t_struct *u, int iter)
{
	int min;
	int i;
	int j;

	min = INT_MAX;
	i = (u->possible_pos[iter][1] - 1 >= 0) ? u->possible_pos[iter][1] : 0;
	while (i < u->possible_pos[iter][1] + 1 && i < u->map_h)
	{
		j = (u->possible_pos[iter][0] - 1 >= 0) ? u->possible_pos[iter][0] : 0;
		while (j < u->possible_pos[iter][0] + 1 && j < u->map_w)
		{
			min = (u->map[i][j] < min) ? u->map[i][j] : min;
			++j;
		}
		i++;
	}
	u->min_dist_adj = (min < u->min_dist_adj) ? min : u->min_dist_adj;
	return (min);
}

int		set_my_pos(t_struct *u)
{
	int i;
	int j;
	int found;
	int iter;

	iter = 0;
	found = 0;
	i = (u->my_c[0] == 'o') ? u->first_o.y - 1 : u->first_x.y - 1;
	while (u->map[++i])
	{
		j = -1;
		found = 0;
		while (u->map[i][++j])
		{
			if (is_me(u, u->map[i][j]) && ++found)
			{
				u->possible_pos[iter][0] = j;
				u->possible_pos[iter++][1] = i;
				//u->possible_pos[iter - 1][2] = find_smallest_val(u, iter - 1);
			}
		}
		if (found == 0)
			break ;
	}
	return (iter);
}

int 	**malloc_2d_int_arr(int **arr, int size_i, int size_j)
{
	int iter;

	arr = (int**)malloc(sizeof(int*) * size_i);
	iter = -1;
	while (++iter < size_i)
		arr[iter] = (int*)malloc(sizeof(int) * size_j);
	return (arr);
}

int		trim_pos(t_struct *u)
{
	int i;
	//int trimmed_pos[u->num_me][2];
	int j;
	int min;

	u->trimmed_pos = malloc_2d_int_arr(u->trimmed_pos, u->num_me, 2);
	min = INT_MAX;
	i = -1;
	while (++i < u->num_me)
	{
		j = find_smallest_val(u, i);
		min = (j < min) ? j : min;

	j = -1;
	i = -1;
	while (++i < u->num_me)
	{
		if (/*u->possible_pos[i][3]*/ (min - 48) == u->min_dist_adj)
		{
			u->trimmed_pos[++j][0] = u->possible_pos[i][0];
			u->trimmed_pos[j][1] = u->possible_pos[i][1];
		}
	}
	return (j);
}

void	update_adj_nbrs(t_struct *u, int num, int x, int y)
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

void	put_adj_nbrs(t_struct *u, int num, int x, int y)
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

char	**make_heatmap(t_struct *u, int num, int xx, int yy)
{
	int x;
	int y;

	x = (u->c == u->his_c[1]) ? u->first_en.x : u->last_played_en.x;
	y = (u->c == u->his_c[1]) ? u->first_en.y : u->last_played_en.y;
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

char	**get_heatmap(t_struct *u)
{
	if (u->last_played_en.x < 0) // first round
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

void	place_piece(t_struct *u)
{

}

void	set_me_his(t_struct *u)
{
	u->my_c[0] = (u->player1) ? 'o' : 'x';
	u->my_c[1] = (u->player1) ? 'O' : 'X';
	u->his_c[0] = (u->player1) ? 'x' : 'o';
	u->his_c[1] = (u->player1) ? 'X' : 'O';
}

void	set_players_pos(t_struct *u)
{
	if (!u->player1)
	{
		u->first_en.x = u->first_o.x;
		u->first_en.y = u->first_o.y;
		u->last_played_en.x = u->last_played_o.x;
		u->last_played_en.y = u->last_played_o.y;
	}
	else
	{
		u->first_en.x = u->first_x.x;
		u->first_en.y = u->first_x.y;
		u->last_played_en.x = u->last_played_x.x;
		u->last_played_en.y = u->last_played_x.y;
	}
}

int		main(int argc, char **argv)
{
	t_struct *u;
	int x;
	int y;
	int **tab;

	if (!(u = init_utils(argv[1])))
		return (-1);
	u->player1 = 1;		// REMOVE
	if ((ft_get_size_map(u)) == -1)
		return (-1); //print error //read only once
	u->map = get_map(u);
	u->symbol = 'x';  // X = x + 32
	if (!(get_piece(u)))
		return (-1);
	set_me_his(u);
	get_piece(u);
	//printf("ok\n");
	ft_print_tab2(u->map);
	printf("\n");
	set_players_pos(u);
	if (u->first_x_on == 1 && u->first_o_on)
		u->map = get_heatmap(u);
	ft_print_tab2(u->map);
	// printf("%s\n", "MAP");
	// printf("map_w == %d\n", u->map_w);
	// printf("map_h == %d\n", u->map_h);
	printf("\n");
	u->map = get_heatmap(u);
	ft_print_tab2(u->map);

	u->num_me = set_my_pos(u);
	printf("#num %d\n", u->num_me);
	u->num_me = trim_pos(u);

	printf("\n");
	int x = 0;
	while (x < u->num_me)
	{
		int y = 0;
		while (y < 2)
		{
			printf("%d ", u->trimmed_pos[x][y]);
			y++;
		}
		printf("\n");
		x++;
	}
	printf("\n");

	//printf("\n%s\n\n", u->trimmed_pos);
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
	// printf("%s\n", "PIECE");
	// ft_print_tab2(u->tmp_shape);
	// printf("last_played_x_on == %d\n", u->last_played_x_on);
	// printf("last_played_o_on == %d\n", u->last_played_o_on);
	// printf("last_played_x.x == %d\n", u->last_played_x.x);
	// printf("last_played_x.y == %d\n", u->last_played_x.y);
	// printf("last_played_o.x == %d\n", u->last_played_o.x);
	// printf("last_played_o.y == %d\n", u->last_played_o.y);
	// printf("\n%s\n", "PIECE");
	// ft_print_tab2(u->tmp_shape);
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
	// print_int2(u->coord, u->piece.total, 2);
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
