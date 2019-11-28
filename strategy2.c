/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 20:26:51 by spozzi            #+#    #+#             */
/*   Updated: 2019/11/28 20:27:30 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	set_max_distances(t_struct *u)
{
	int i;
	int s_x;
	int s_y;

	i = -1;
	s_x = u->piece.coord[u->curr_piece_fulcrum][0];
	s_y = u->piece.coord[u->curr_piece_fulcrum][1];
	init_borders(u, s_x, s_y);
	while (++i < u->piece.total)
	{
		if (i != u->curr_piece_fulcrum)
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
	center_borders(u, s_x, s_y);
}

int		tmp_place_all(t_struct *u, int **solutions)
{
	u->x = u->trimmed_pos[u->best_pos][0];
	u->y = u->trimmed_pos[u->best_pos][1];
	u->origin_x = u->piece.coord[u->curr_piece_fulcrum][0];
	u->origin_y = u->piece.coord[u->curr_piece_fulcrum][1];
	solutions[u->curr_piece_fulcrum][0] = INT_MAX;
	u->i = -1;
	while (++u->i < u->piece.total)
		if (u->i != u->curr_piece_fulcrum)
			if (u->h_map[u->y + (u->origin_y - u->piece.coord[u->i][1]) * -1]
						[u->x + (u->origin_x - u->piece.coord[u->i][0]) * -1]
						< solutions[u->curr_piece_fulcrum][0])
			{
				solutions[u->curr_piece_fulcrum][0] = u->h_map
				[u->y + (u->origin_y - u->piece.coord[u->i][1]) * -1]
				[u->x + (u->origin_x - u->piece.coord[u->i][0]) * -1];
			}
	if (solutions[u->curr_piece_fulcrum][0] == 0)
		return (0);
	u->i = -1;
	solutions[u->curr_piece_fulcrum][1] = 0;
	while (++u->i < u->piece.total)
		if (u->h_map[u->y + (u->origin_y - u->piece.coord[u->i][1]) * -1]
					[u->x + (u->origin_x - u->piece.coord[u->i][0]) * -1]
					== solutions[u->curr_piece_fulcrum][0])
			solutions[u->curr_piece_fulcrum][1]++;
	u->placed_one = 1;
	return (1);
}

int		place_all_poss(t_struct *u, int **solutions)
{
	u->curr_piece_fulcrum = -1;
	while (++u->curr_piece_fulcrum < u->piece.total)
	{

		set_max_distances(u);
		while ((((u->trimmed_pos[u->best_pos][1] + u->piece.down >= u->map_h)
				|| (u->trimmed_pos[u->best_pos][1] - u->piece.up < 0)
				|| (u->trimmed_pos[u->best_pos][0] + u->piece.right >= u->map_w)
				|| (u->trimmed_pos[u->best_pos][0] - u->piece.left < 0))
				&& ++u->curr_piece_fulcrum))
				{
					if (u->curr_piece_fulcrum == u->piece.total)
						return (0);
					set_max_distances(u);
				}
		tmp_place_all(u, solutions);
	}
	return (u->placed_one);
}

/*
**		More than one fulcrum with the same min value was found
**		Find the one with highest cardinality
*/

void	trim_to_min_highest_occurance(t_struct *u, int **solutions, int min)
{
	int i;
	int j;

	i = -1;
	while (++i < u->piece.total)
	{
		j = i;
		while (++j < u->piece.total)
		{
			if (solutions[i][0] == min && solutions[j][0] == min)
			{
				if (solutions[i][1] < solutions[j][1])
				{
					solutions[i][0] = 0;
					i = 0;
				}
				else if (solutions[i][1] > solutions[j][1])
				{
					solutions[j][0] = 0;
					j = 0;
				}
			}
		}
	}
}

/*
**		1) Finds min value piece is placed on
**		2) Finds how many different fulcri have that same main
**		3) If more than one fulcrum found select the one with most occurrances
**			of min
*/

int		find_best_sol(t_struct *u, int **solutions)
{
	int i;
	int num_best;
	int min;


	i = -1;
	min = INT_MAX;
	while (++i < u->piece.total)
		if (solutions[i][0] < min && solutions[i][0] > 0)
			min = solutions[i][0];
	i = -1;
	num_best = 0;
	while (++i < u->piece.total)
		if (solutions[i][0] == min)
			num_best++;
	if (num_best > 1)
		trim_to_min_highest_occurance(u, solutions, min);
	i = -1;
	while (++i < u->piece.total)
		if(solutions[i][0] == min)
			break ;
	return (i);
}
