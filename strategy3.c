/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 20:28:23 by spozzi            #+#    #+#             */
/*   Updated: 2019/11/28 20:28:32 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

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
