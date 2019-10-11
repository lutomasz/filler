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

void ft_put_first(t_struct *utils)
{
	//coord = [first_x_x - shift_up][first_x_y - shift_left]
	//printf("%d\n", utils->first_x_x - utils->shift_haut);
	//printf("%d\n", utils->first_x_y - utils->shift_gauche);
	// write
	exit (1);
}

int strategy_1(t_struct *utils)
{
	int i;
	int count;
	int j;

	i = 0;
	count = 0;

	while (utils->tmp_map[i])
	{
		j = 0;
		while (utils->tmp_map[i][j])
		{
			if (utils->tmp_map[i][j] == 'X')
				count++;
			j++;
		}
		i++;
	}
	if (count == 1)
	{

		ft_put_first(utils);
		printf("ok");
		return (1);
	}
	return (0);
}


void ft_filler(t_struct *utils)
{
	if (strategy_1(utils) == 1)
		exit (1);
	
}


int main(int argc, char **argv)
{
	t_struct *utils;
	

	utils = init_utils();

	ft_get_size_map(utils);
	utils->tmp_map = get_tmp_map(utils);
	get_piece(utils);
	//ft_filler(utils);
	ft_print_tab2(utils->tmp_map);

	printf("%s\n", "MAP");
	printf("map_x == %d\n", utils->map_x);
	printf("map_y == %d\n", utils->map_y);
	printf("%s\n", "MATRIX");
	printf("first_x_on == %d\n", utils->first_x_on);
	printf("first_o_on == %d\n", utils->first_o_on);
	printf("first_o.x == %d\n", utils->first_o.x);
	printf("first_o.y == %d\n", utils->first_o.y);
	printf("first_x.x == %d\n", utils->first_x.x);
	printf("first_x.y == %d\n", utils->first_x.y);
	printf("last_played_x_on == %d\n", utils->last_played_x_on);
	printf("last_played_o_on == %d\n", utils->last_played_o_on);
	printf("last_played_x.x == %d\n", utils->last_played_x.x);
	printf("last_played_x.y == %d\n", utils->last_played_x.y);
	printf("last_played_o.x == %d\n", utils->last_played_o.x);
	printf("last_played_o.y == %d\n", utils->last_played_o.y);
	printf("%s\n", "PIECE");
	ft_print_tab2(utils->tmp_shape);
	printf("%s\n", "SHAPE");
	ft_print_tab2(utils->shape);
	printf("utils->shift.left == %d\n", utils->shift.left);
	printf("utils->shift.up == %d\n", utils->shift.up);
	printf("utils->down_shift == %d\n", utils->shift.down);
	printf("utils->right_shift == %d\n", utils->shift.right);
	printf("\n");
	printf("utils->piece_h == %d\n", utils->piece.h);
	printf("utils->piece_w == %d\n", utils->piece.w);
	printf("utils->piece.first_x == %d\n", utils->piece.first_x);
	printf("utils->piece.first_y == %d\n", utils->piece.first_y);
	printf("utils->piece.last_x == %d\n", utils->piece.last_x);
	printf("utils->piece.last_y == %d\n", utils->piece.last_y);


	//ft_filler(utils);
}