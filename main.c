/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 20:04:39 by lutomasz          #+#    #+#             */
/*   Updated: 2019/03/11 20:04:41 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void ft_put_first(t_struct *u)
{
	//coord = [first_x_x - shift_up][first_x_y - shift_left]
	//printf("%d\n", u->first_x_x - u->shift_haut);
	//printf("%d\n", u->first_x_y - u->shift_gauche);
	// write
	exit (1);
}

int strategy_1(t_struct *u)
{
	int i;
	int count;
	int j;

	i = 0;
	count = 0;

	while (u->tmp_map[i])
	{
		j = 0;
		while (u->tmp_map[i][j])
		{
			if (u->tmp_map[i][j] == 'X')
				count++;
			j++;
		}
		i++;
	}
	if (count == 1)
	{

		ft_put_first(u);
		printf("ok");
		return (1);
	}
	return (0);
}


void ft_filler(t_struct *u)
{
	if (strategy_1(u) == 1)
		exit (1);
	
}


int main(int argc, char **argv)
{
	t_struct *u;
	int x;
	int y;

	u = init_utils();

	ft_get_size_map(u);
	u->tmp_map = get_tmp_map(u);
	get_piece(u);
	//ft_filler(u);
	ft_print_tab2(u->tmp_map);

	// printf("%s\n", "MAP");
	// printf("map_x == %d\n", u->map_x);
	// printf("map_y == %d\n", u->map_y);
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
	// ft_print_tab2(u->shape);
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
	// ft_print_tab2(u->coord);
	printf("coord\n");
	x = 0;
	while (x < u->piece.total)
	{
		y = 0;
		while (y < 2)
		{
			printf("%d", u->coord[x][y]);
			y++;
		}
		printf("\n");
		x++;
	} 

	//ft_filler(u);
}