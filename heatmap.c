/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 13:25:51 by spozzi            #+#    #+#             */
/*   Updated: 2019/11/09 11:14:54 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	put_adj_nbrs(t_struct *u, int num, int x, int y)
{
	int i;
	int j;

	i = -2;
	while (++i < 2)
	{
		if (y + i >= 0 && y + i < u->map_h)
		{
			j = -2;
			while (++j < 2 && x + j < u->map_w)
			{
				if ((u->h_map[y + i][x + j] > num
						|| u->map[y + i][x + j] == '.')
						&& !is_enemy(u, u->map[y + i][x + j]) && (y + i >= 0 && x + j >= 0))
				{
					//printf("c = %c (%d, %d)\n", u->map[y + i][x + j], y + i, x + j);
					u->map[y + i][x + j] = ',';
					u->h_map[y + i][x + j] = num + 1;
				}

			}	
		}
		//print_int2(u->h_map, u->map_w, u->map_h);
		//ft_print_tab2(u->map);
	}
}

char	**make_heatmap(t_struct *u, int num, int xx, int yy)
{
	int x;
	int y;

	x = (u->c == u->his_c[1]) ? u->first_en.x : u->last_played_en.x;
	y = (u->c == u->his_c[1]) ? u->first_en.y : u->last_played_en.y;
	x = (xx >= 0) ? xx : x;
	y = (xx >= 0) ? yy : y;
	update_adj_nbrs(u, 1, x, y);
	num = 1;
	while(!no_dots(u))
	{
		y = -1;
		while (++y < u->map_h)
		{
			x = -1;
			while (++x < u->map_w)
			{
				//printf("%d\n", u->h_map[y][x]);
				if (u->h_map[y][x] == num)
					put_adj_nbrs(u, num, x, y);
			}
		}
		++num;
	}
	return (u->map);
}

void	update_adj_nbrs(t_struct *u, int num, int x, int y)
{
	int i;
	int j;

	i = -2;
	u->map[y][x] = (64 < u->map[y][x] && u->map[y][x] < 91) ? 'A' : 'a';
	while (++i < 2)
	{
		if (y + i >= 0 && y + i < u->map_h)
		{
			j = -2;
			while (++j < 2)
			{
				if (i == 0 && j == 0)
					++j;
				if (x + j >= 0 && x + j < u->map_w)
				{
					if ((u->map[y + i][x + j] == '.' || u->h_map[y + i][x + j]
							 > num) && !is_enemy(u, u->map[y + i][x + j]))
					{
						u->map[y + i][x + j] = ',';
						u->h_map[y + i][x + j] = num;
					}
					if (is_enemy(u, u->map[y + i][x + j]))
						make_heatmap(u, 1, x + j, y + i);
				}
			}
		}
	}
}

char	**get_heatmap(t_struct *u)
{
	if (u->last_played_en.x < 0) // first round
	{
		u->c = u->his_c[1];
		return(make_heatmap(u, 0, -1, -1));
	}
	else
	{
		u->c = u->his_c[0];
		return(make_heatmap(u, 0, -1, -1));
	}
}
