/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 18:30:20 by spozzi            #+#    #+#             */
/*   Updated: 2019/12/01 18:30:34 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		find_smallest_val(t_struct *u, int iter)
{
	int min;
	int i;
	int j;

	min = INT_MAX;
	i = (u->possible_pos[iter][1] - 1 >= 0) ? u->possible_pos[iter][1] - 1 : 0;
	while (i <= u->possible_pos[iter][1] + 1 && i < u->map_h)
	{
		j = (u->possible_pos[iter][0] - 1 >= 0)
			? u->possible_pos[iter][0] - 1 : 0;
		while (j <= u->possible_pos[iter][0] + 1 && j < u->map_w)
		{
			if (!is_me(u, u->map[i][j]))
				min = (u->h_map[i][j] < min && u->h_map[i][j] != 0)
				? u->h_map[i][j] : min;
			++j;
		}
		i++;
	}
	u->min_dist_adj = (min < u->min_dist_adj) ? min : u->min_dist_adj;
	return (min);
}
