/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:02:43 by spozzi            #+#    #+#             */
/*   Updated: 2019/11/28 20:21:12 by spozzi           ###   ########.fr       */
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
	int i;
	int j;
	int indx;
	int	cntr[u->num_me];

	i = -1;
	while (++i < u->num_me)
		cntr[i] = 0;
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
					&& u->trimmed_pos[indx][0] + j >= 0
					&& u->trimmed_pos[indx][1] + i >= 0
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

int		atleast_one_placed(t_struct *u)
{
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

int		find_next_opp_in_line(t_struct *u, int x, int y)
{
	while (++x < u->map_w)
	{
		if (u->map[y][x] == 'a' || u->map[y][x] == 'A')
			return (x);
	}
	return (-1);
}

int		is_enclosed(t_struct *u, int x, int y)
{
	int i;
	int j;

	i = -2;
	while (++i <= 1)
	{
		j = -2;
		while (++j <= 1)
		{
			if (!(y + i < 0 || x + j < 0 ||
				y + i >= u->map_h || x + j >= u->map_w))
				if (u->map[y + i][x + j] == '.' || u->map[y + i][x + j] == ',')
					return (0);
		}
	}
	return (1);
}

int		is_not_enclosed(t_struct *u, int *is_opp_enclosed)
{
	int x;
	int y;

	if (*is_opp_enclosed)
		return (0);
	y = (u->his_c[0] == 'o') ? u->first_o.y : u->first_x.y;
	x = 0;
	while (y < u->map_h)
	{
		x = find_next_opp_in_line(u, x, y);
		if (x >= 0)
		{
			if (!is_enclosed(u, x, y))
				return (1);
		}
		else
			++y;
	}
	*is_opp_enclosed = 1;
	return (0);
}

int		place_piece3(t_struct *u, int *is_opp_enclosed, int cheat, int **sol)
{
	if (u->ret != 0 && !cheat)
	{
		u->bst_i = find_best_sol(u, sol);
		if (u->bst_i == u->piece.total)
		{
			if (!other_place(u))
			{
				ft_putnbr(0);
				ft_putchar(' ');
				ft_putnbr(0);
				ft_putchar('\n');
				free_double_int(sol, u->piece.total);
				return (0);
			}
			free_double_int(sol, u->piece.total);
			return (1);
		}
		u->sol_x = u->trimmed_pos[u->best_pos][0] - u->piece.coord[u->bst_i][0];
		u->sol_y = u->trimmed_pos[u->best_pos][1] - u->piece.coord[u->bst_i][1];
	}
	free_double_int(sol, u->piece.total);
	return (1);
}

int		place_piece2(t_struct *u, int *is_opp_enclosed, int **sol)
{
	int cheat;

	cheat = 0;
	if (u->ret == 0 || (u->trimmed_pos[u->best_pos][0]
		- u->piece.coord[u->bst_i][0] <= 0 && u->trimmed_pos[u->best_pos][1]
		- u->piece.coord[u->bst_i][1] <= 0))
	{
		cheat = 1;
		if (!other_place(u))
		{
			ft_putnbr(0);
			ft_putchar(' ');
			ft_putnbr(0);
			ft_putchar('\n');
			free_double_int(sol, u->piece.total);
			return (0);
		}
	}
	return (place_piece3(u, is_opp_enclosed, cheat, sol));
}

int		place_piece(t_struct *u, int *is_opp_enclosed)
{
	int **solutions;

	if (!(solutions = malloc_2d_int_arr(solutions, u->piece.total, 2)))
		return (0);
	u->i = -1;
	while (++u->i < u->piece.total)
	{
		solutions[u->i][0] = 0;
		solutions[u->i][1] = 0;
	}
	u->placed_one = 0;
	if (is_not_enclosed(u, is_opp_enclosed))
	{
		u->ret = place_all_poss(u, solutions);
		if (u->ret == 0)
		{
			u->best_pos = 0;
			while (u->ret == 0 && u->best_pos < u->num_me)
			{
				u->ret = place_all_poss(u, solutions);
				u->best_pos++;
			}
			u->best_pos--;
		}
	}
	return (place_piece2(u, is_opp_enclosed, solutions));
}


// int		place_piece(t_struct *u, int *is_opp_enclosed)
// {
// 	int **solutions;
// 	int best_sol_i;
// 	int ret;
// 	int cheat;
//
// 	if (!(solutions = malloc_2d_int_arr(solutions, u->piece.total, 2)))
// 		return (0);
// 	u->i = -1;
// 	while (++u->i < u->piece.total)
// 	{
// 		solutions[u->i][0] = 0;
// 		solutions[u->i][1] = 0;
// 	}
// 	u->placed_one = 0;
// 	if (is_not_enclosed(u, is_opp_enclosed))
// 	{
// 		ret = place_all_poss(u, solutions);
// 		if (ret == 0)
// 		{
// 			u->best_pos = 0;
// 			while (ret == 0 && u->best_pos < u->num_me)
// 			{
// 				ret = place_all_poss(u, solutions);
// 				u->best_pos++;
// 			}
// 			u->best_pos--;
// 		}
// 	}
// 	cheat = 0;
// 	if (ret == 0 || (u->trimmed_pos[u->best_pos][0] - u->piece.coord[best_sol_i][0] <= 0 && u->trimmed_pos[u->best_pos][1] - u->piece.coord[best_sol_i][1] <= 0))
// 	{
// 		cheat = 1;
// 		if (!other_place(u))
// 		{
// 			ft_putnbr(0);
// 			ft_putchar(' ');
// 			ft_putnbr(0);
// 			ft_putchar('\n');
// 			free_double_int(solutions, u->piece.total);
// 			return (0);
// 		}
// 	}
// 	if (ret != 0 && !cheat)
// 	{
// 		best_sol_i = find_best_sol(u, solutions);
// 		if (best_sol_i == u->piece.total)
// 		{
// 			if (!other_place(u))
// 			{
// 				ft_putnbr(0);
// 				ft_putchar(' ');
// 				ft_putnbr(0);
// 				ft_putchar('\n');
// 				free_double_int(solutions, u->piece.total);
// 				return (0);
// 			}
// 			free_double_int(solutions, u->piece.total);
// 			return (1);
// 		}
// 		u->sol_x = u->trimmed_pos[u->best_pos][0] - u->piece.coord[best_sol_i][0];
// 		u->sol_y = u->trimmed_pos[u->best_pos][1] - u->piece.coord[best_sol_i][1];
// 	}
// 	free_double_int(solutions, u->piece.total);
// 	return (1);
// }
