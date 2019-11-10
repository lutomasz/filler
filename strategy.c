/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:02:43 by spozzi            #+#    #+#             */
/*   Updated: 2019/11/10 16:23:52 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		get_best_placing_slot(t_struct *u, int cntr[u->num_me])
{
	int i;
	int res;
	int max;

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
	if (max >= 0)	// MAYBE CHANGE COZ HERE WE USE ONLY THE LAST OCCURRENCE OF THE BEST POSSIBLE PIECE
		u->num_me = 1;
	return (res);
}

int		check_adj_num(t_struct *u)
{
	int i;
	int j;
	int indx;
	int	cntr[u->num_me];

	indx = -1;
	while (++indx < u->num_me)
	{
		i = -2;
		while (++i < 2)
		{
			j = -2;
			while (++j < 2)
			{
				cntr[indx] += (u->trimmed_pos[indx][0] + j < u->map_w
					&& u->trimmed_pos[indx][0] - j >= 0
					&& u->trimmed_pos[indx][1] - i >= 0
					&& u->trimmed_pos[indx][1] + i < u->map_h
					&& u->h_map[u->trimmed_pos[indx][1] + i]
					[u->trimmed_pos[indx][0] + j] == u->trimmed_pos[indx][2])
					? 1 : 0;
			}
		}
	}
	return (get_best_placing_slot(u, cntr));
}

void	select_pos(t_struct *u)
{
	int		flag;

	flag = 0;
	u->best_pos = check_adj_num(u);
	if (u->best_pos)
		printf("FUCKED UP BEST_POS\n");
	//u->curr_piece_fulcrum = 0;
	if (u->num_me > 1)
	{
		//srand (time(NULL));
		u->best_pos = (rand() % (u->num_me));
	}
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

int		tmp_place_all(t_struct *u, int solutions[u->piece.total][2])
{
	u->x = u->trimmed_pos[u->best_pos][0];
	u->y = u->trimmed_pos[u->best_pos][1];
	u->origin_x = u->piece.coord[u->curr_piece_fulcrum][0];
	u->origin_y = u->piece.coord[u->curr_piece_fulcrum][1];
	solutions[u->curr_piece_fulcrum][0] = INT_MAX;
	u->i = -1;
	while (++u->i < u->piece.total)
		if (u->i != u->curr_piece_fulcrum)
			if (u->h_map[u->y + (u->origin_y - u->piece.coord[u->i][1])*-1]
						[u->x + (u->origin_x - u->piece.coord[u->i][0])*-1]
						< solutions[u->curr_piece_fulcrum][0])
				solutions[u->curr_piece_fulcrum][0] = u->h_map
							[u->y + (u->origin_y - u->piece.coord[u->i][1])*-1]
							[u->x + (u->origin_x - u->piece.coord[u->i][0])*-1];
	if (solutions[u->curr_piece_fulcrum][0] == 0)
		return (0);
	u->i = -1;
	solutions[u->curr_piece_fulcrum][1] = 0;
	while (++u->i < u->piece.total)
		if (u->h_map[u->y + (u->origin_y - u->piece.coord[u->i][1])*-1]
					[u->x + (u->origin_x - u->piece.coord[u->i][0])*-1]
					== solutions[u->curr_piece_fulcrum][0])
			solutions[u->curr_piece_fulcrum][1]++;
	printf("sol: %d %d\n\n", solutions[u->curr_piece_fulcrum][0], solutions[u->curr_piece_fulcrum][1]);
	return (1);
}

int		atleast_one_placed(t_struct *u)
{

}

int		place_all_poss(t_struct *u, int solutions[u->piece.total][2])
{
	if (u->curr_piece_fulcrum == u->piece.total)
	{
		if (atleast_one_placed(u))
			return (1);			// worked
		else
			return (0);			// NEED TO FIND ANOTHER SOLUTION!!!!!!!!! <----------------------
	}
	set_max_distances(u);
	if ((((u->trimmed_pos[u->best_pos][1] + u->piece.down >= u->map_h)
			|| (u->trimmed_pos[u->best_pos][1] - u->piece.up < 0)
			|| (u->trimmed_pos[u->best_pos][0] + u->piece.right >= u->map_w)
			|| (u->trimmed_pos[u->best_pos][0] + u->piece.down < 0))
			&& ++u->curr_piece_fulcrum))
		place_all_poss(u, solutions);
	// sleep(100000000);
	tmp_place_all(u, solutions);  //stock smallest value overlapping
	++u->curr_piece_fulcrum;
	place_all_poss(u, solutions);
	return (1);
}
/*
	*	More than one fulcrum with the same min value was found
	*	Find the one with highest cardinality
*/
void	trim_to_min_highest_occurance(t_struct *u, int solutions[u->piece.total][2], int min)
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
					i = -1;
				}
				else if (solutions[i][1] > solutions[j][1])
				{
					solutions[j][0] = 0;
					i = -1;
				}
			}
		}
	}
}
/*
	*	1) Finds min value piece is placed on
	*	2) Finds how many different fulcri have that same main
	*	3) If more than one fulcrum found select the one with most occurrances
	*		of min
*/
int		find_best_sol(t_struct *u, int solutions[u->piece.total][2])
{
	int i;
	int num_best;
	int min;

	i = -1;
	min = INT_MAX;
	while (++i < u->piece.total)	// find min value
		if(solutions[i][0] < min)
			min = solutions[i][0];
	i = -1;
	num_best = 0;
	while (++i < u->piece.total)
		if(solutions[i][0] == min)	// find how many solutions have min value
			num_best++;
	if (num_best > 1)
		trim_to_min_highest_occurance(u, solutions, min);
	i = -1;
	while (++i < u->piece.total)
		if(solutions[i][0] == min)
			break ;
	return (i);
}

void	place_piece(t_struct *u)
{
	int solutions[u->piece.total][2];	// 0-> min num && 1 -> cardinality
	int best_sol_i;

	place_all_poss(u, solutions);
	best_sol_indx = find_best_sol(u, solutions);
	u->sol_x = u->trimmed_pos[u->best_pos][0] - u->piece.coord[best_sol_i][0];
	u->sol_y = u->trimmed_pos[u->best_pos][1] - u->piece.coord[best_sol_i][1];
}
