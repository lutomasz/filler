/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <lutomasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 20:04:39 by lutomasz          #+#    #+#             */
/*   Updated: 2019/12/01 17:56:55 by spozzi           ###   ########.fr       */
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

int		set_my_pos(t_struct *u)
{
	int i;
	int j;
	int found;
	int iter;

	iter = 0;
	i = (u->my_c[0] == 'o') ? u->first_o.y - 1 : u->first_x.y - 1;
	while (++i < u->map_h)
	{
		j = -1;
		found = 0;
		while (++j < u->map_w)
		{
			if (is_me(u, u->map[i][j]) && ++found)
			{
				u->possible_pos[iter][0] = j;
				u->possible_pos[iter][1] = i;
				u->possible_pos[iter][2] = find_smallest_val(u, iter);
				iter++;
			}
		}
		if (found == 0)
			break ;
	}
	return (iter);
}

int		trim_pos(t_struct *u)
{
	int i;
	int j;
	int min;

	if (!(u->trimmed_pos = malloc_2d_int_arr(u->trimmed_pos, u->num_me, 2)))
		return (-1);
	min = INT_MAX;
	i = -1;
	j = 0;
	i = -1;
	u->num_of_trims = u->num_me;
	while (++i < u->num_me)
	{
		if (u->possible_pos[i][2] == u->min_dist_adj)
		{
			u->trimmed_pos[j][0] = u->possible_pos[i][0];
			u->trimmed_pos[j][1] = u->possible_pos[i][1];
			u->trimmed_pos[j++][2] = u->possible_pos[i][2];
		}
	}
	return (j);
}

int		init_parse(t_struct *u, int *i)
{
	if (init_utils(u) == -1)
		return (-1);
	if ((ft_get_size_map(u, i)) == -1)
		return (-1);
	if (get_map(u) == 0)
		return (-1);
	if (!(get_piece(u)))
		return (free_all(u, -1));
	return (1);
}

/*
** main with infinite loop
*/

int		main2(t_struct *u, int *is_opp_enclosed, int *i)
{
	if (init_parse(u, i) == -1)
		return (-1);
	u->sam = (u->sam == 0) ? u->map_w : u->sam;
	u->player1 = *i;
	if (!(u->possible_pos = malloc_2d_int_arr(u->possible_pos, u->map_h * u->map_w, 3)))
		return (-1);
	set_me_his(u);
	set_players_pos(u);
	get_heatmap(u);
	u->num_me = set_my_pos(u);
	u->num_me = trim_pos(u);
	select_pos(u);
	if (!(u->smallest_val = (int*)(malloc(sizeof(int) * u->num_me)))) // use index of smallest value to decide which piece overlaps
		return (-1);
	u->sam -= 10;
	u->sam = (u->sam < 1) ? 1 : u->sam;
	if (place_piece(u, is_opp_enclosed))
		print_sol(u);
	else
		return (0);
	return (1);
}

int		main(void)
{
	t_struct	u;
	static int	i;
	int			is_opp_enclosed;
	int 		ret;

	ret = 1;
	i = 0;
	is_opp_enclosed = 0;
	u.map_h = 0;
	while (1)
	{
		ret = main2(&u, &is_opp_enclosed, &i);
		if (ret != 1)
			break ;
	}
	free_all(&u, 0);
	if (u.h_map != 0)
		free_double_int(u.h_map, u.map_h);
	return (0);
}
