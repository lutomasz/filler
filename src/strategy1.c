/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 20:25:26 by spozzi            #+#    #+#             */
/*   Updated: 2019/11/28 20:38:56 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		get_best_placing_slot(t_struct *u, int cntr[u->num_me])
{
	int		i;
	int		res;
	int		max;

	i = -1;
	max = -1;
	res = -1;
	while (++i < u->num_me)
	{
		if (cntr[i] > max)
		{
			max = cntr[i];
			res = i;
		}
	}
	return (res);
}

/*
**		Counts how many slots adjacent to the best possible positions have the
**		min value
**		RETURN: index of the best position in "trim_pos"
*/

int		check_adj_num(t_struct *u)
{
	int indx;
	int	cntr[u->num_me];

	u->i = -1;
	while (++u->i < u->num_me)
		cntr[u->i] = 0;
	indx = -1;
	while (++indx < u->num_me)
	{
		u->i = -2;
		while (++u->i < 2)
		{
			u->j = -2;
			while (++u->j < 2)
				cntr[indx] += (u->trimmed_pos[indx][0] + u->j < u->map_w
					&& u->trimmed_pos[indx][0] + u->j >= 0
					&& u->trimmed_pos[indx][1] + u->i >= 0
					&& u->trimmed_pos[indx][1] + u->i < u->map_h
					&& u->h_map[u->trimmed_pos[indx][1] + u->i]
					[u->trimmed_pos[indx][0] + u->j] == u->trimmed_pos[indx][2])
					? 1 : 0;
		}
	}
	return (get_best_placing_slot(u, cntr));
}

void	select_pos(t_struct *u)
{
	int		flag;

	flag = 0;
	u->best_pos = check_adj_num(u);
}

void	init_borders(t_struct *u, int s_x, int s_y)
{
	u->piece.down = s_y;
	u->piece.up = s_y;
	u->piece.left = s_x;
	u->piece.right = s_x;
}

void	center_borders(t_struct *u, int s_x, int s_y)
{
	u->piece.down -= s_y;
	u->piece.up -= s_y;
	u->piece.left -= s_x;
	u->piece.right -= s_x;
	u->piece.up *= -1;
	u->piece.left *= -1;
}
