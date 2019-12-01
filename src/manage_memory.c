/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:02:23 by lutomasz          #+#    #+#             */
/*   Updated: 2019/11/27 17:02:31 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		free_str2(char **str, int return_val)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (return_val);
}

int		free_double_int(int **str, int elements)
{
	int i;

	i = -1;
	while (++i < elements && str[i])
		free(str[i]);
	free(str);
	return (0);
}

int		free_all(t_struct *u, int return_val)
{
	if (u->smallest_val)
		free(u->smallest_val);
	if (u->piece.coord)
		free_double_int(u->piece.coord, u->piece.total);
	if (u->trimmed_pos)
		free_double_int(u->trimmed_pos, u->num_of_trims);
	if (u->possible_pos)
		free_double_int(u->possible_pos, u->map_h * u->map_w);
	if (u->tmp_shape)
		free_str2(u->tmp_shape, 0);
	if (u->map)
		free_str2(u->map, 0);
	return (return_val);
}

int		free_unset_tab(char **str, int cnt, int return_val)
{
	int i;

	i = -1;
	while (++i < cnt - 1)
		free(str[i]);
	free(str);
	return (return_val);
}
