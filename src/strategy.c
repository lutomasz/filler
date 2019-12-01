/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:02:43 by spozzi            #+#    #+#             */
/*   Updated: 2019/11/28 20:55:40 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

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
		if ((u->ret = place_all_poss(u, solutions)) == 0)
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
