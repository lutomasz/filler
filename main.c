/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <lutomasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 20:04:39 by lutomasz          #+#    #+#             */
/*   Updated: 2019/10/12 16:44:28 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int test(int i)
{
	return (i*i);
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

	printf("%s\n", "MAP");
	printf("map_x == %d\n", u->map_x);
	printf("map_y == %d\n", u->map_y);
	printf("%s\n", "MATRIX");
	printf("first_x_on == %d\n", u->first_x_on);
	printf("first_o_on == %d\n", u->first_o_on);
	printf("first_o.x == %d\n", u->first_o.x);
	printf("first_o.y == %d\n", u->first_o.y);
	printf("first_x.x == %d\n", u->first_x.x);
	printf("first_x.y == %d\n", u->first_x.y);
	printf("last_played_x_on == %d\n", u->last_played_x_on);
	printf("last_played_o_on == %d\n", u->last_played_o_on);
	printf("last_played_x.x == %d\n", u->last_played_x.x);
	printf("last_played_x.y == %d\n", u->last_played_x.y);
	printf("last_played_o.x == %d\n", u->last_played_o.x);
	printf("last_played_o.y == %d\n", u->last_played_o.y);
	printf("%s\n", "PIECE");
	ft_print_tab2(u->tmp_shape);
	printf("%s\n", "SHAPE");
	if (u->piece.total > 0)
		ft_print_tab2(u->shape);
	printf("shift.left == %d\n", u->shift.left);
	printf("shift.up == %d\n", u->shift.up);
	printf("down_shift == %d\n", u->shift.down);
	printf("right_shift == %d\n", u->shift.right);
	printf("\n");
	printf("piece_h == %d\n", u->piece.h);
	printf("piece_w == %d\n", u->piece.w);
	printf("piece.first_x == %d\n", u->piece.first_x);
	printf("piece.first_y == %d\n", u->piece.first_y);
	printf("piece.last_x == %d\n", u->piece.last_x);
	printf("piece.last_y == %d\n", u->piece.last_y);
	printf("piece.total == %d\n", u->piece.total);
	printf("\n");
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
