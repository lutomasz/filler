/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:02:43 by spozzi            #+#    #+#             */
/*   Updated: 2019/10/23 17:49:13 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	select_pos(t_struct *u)
{
	u->f_pos_i = 0;
	if (u->num_me > 1)
	{
		//srand (time(NULL));
		u->f_pos_i = (rand() % (u->num_me));
	}
}

void	init_borders(t_struct *u)
{
	u->piece.down = s_y;
	u->piece.up = s_y;
	u->piece.left = s_x;
	u->piece.right = s_x;
}

void	center_borders(t_struct *u)
{
	u->piece.down -= s_y;
	u->piece.up -= s_y;
	u->piece.left -= s_x;
	u->piece.right -= s_x;
	u->piece.up *= -1;
	u->piece.left *= -1;
}

void	set_max_distances(t_struct *u)
{
	int i;
	int s_x;
	int s_y;

	i = -1;
	u->f_pos_i = 2;
	s_x = u->piece.coord[u->f_pos_i][0];
	s_y = u->piece.coord[u->f_pos_i][1];
	init_borders(u);
	while (++i < u->piece.total)
	{
		if (i = u->f_pos_i)
		{
			if (u->piece.coord[i][1] > u->piece.down)
				u->piece.down = u->piece.coord[i][1];
			if (u->piece.coord[i][0] > u->piece.right)
				u->piece.right = u->piece.coord[i][0];
			if (u->piece.coord[i][0] < u->piece.left)
				u->piece.left = u->piece.coord[i][0];
			if (u->piece.coord[i][1] < u->piece.up)
				u->piece.up = u->piece.coord[i][1];
		}
	}
	center_borders(u);
	//printf("here: x: %d		y: %d\n", s_x, s_y);
	//printf("d: %d 	u: %d\nl: %d 	r: %d\n", u->piece.down, u->piece.up, u->piece.left, u->piece.right);
}

void	place(t_struct *u)
{
	// u->piece.h
	// u->piece.w
	// u->piece.coord
	// u->piece.shift
	char smallest_val[u->num_me];
	set_max_distances(u);
}
