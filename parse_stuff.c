/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <lutomasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 02:19:49 by lutomasz          #+#    #+#             */
/*   Updated: 2019/10/23 19:36:10 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_struct	*init_utils(char *map)
{
	t_struct *u;

	if (!(u = (t_struct*)malloc(sizeof(t_struct))) ||
		(u->fd = open(map, O_RDONLY)) < 0)
		return (NULL);
	u->map_w = 0;
	u->map_h = 0;
	//first on map
	u->first_x_on = 0;
	u->first_o_on = 0;
	u->first_o.x = -100;
	u->first_o.y = -100;
	u->first_x.x = -100;
	u->first_x.y = -100;
	//last on map
	u->last_played_x_on = 0;
	u->last_played_o_on = 0;
	u->last_played_x.x = -100;
	u->last_played_x.y = -100;
	u->last_played_o.x = -100;
	u->last_played_o.y = -100;
	//piece
	u->shape = NULL;
	u->tmp_shape = NULL;
	u->piece.coord = NULL;
	u->smallest_val = 0;
	//shifts
	u->shift.left = 0;
	u->shift.up = 0;
	u->shift.down = 0;
	u->shift.right = 0;
	//piece_data
	u->piece.h = 0;
	u->piece.w = 0;
	u->piece.first_x = -100;
	u->piece.first_y = -100;
	u->piece.last_x = -100;
	u->piece.last_y = -100;
	u->piece.total = 0;
	//others
	u->player1 = 0;
	u->en = NULL;
	u->me = NULL;
	u->h_map = 0;
	u->min_dist_adj = INT_MAX;
	return (u);
}

/*
*** print an error message when wrong imput
*/

void		usage(void)
{
	ft_putendl("insert correct map");
}

char		*copy_line(char *str)
{
	int		i;
	int		s;
	char	*tab;

	i = 0;
	if (*str)
	{
		while ((((str[i] != 'X' && str[i] != 'x') && str[i] != 'o' &&
				str[i] != 'O')) && str[i] != '.')
			i++;
		s = i;
		while (str[i] != '\n' && str[i] != '\0')
			i++;
		if (!(tab = ft_strsub(str, s, i)))
			return (NULL);
		return (tab);
	}
	return (NULL);
}

/*
**	analyse the new tab && get first/last position played on for each player
*/

void		first_and_last_map(char **tab, int i, int j, t_struct *u)
{
	if (tab[i][j] == 'X' && u->first_x_on == 0)
	{
		u->first_x_on = 1;
		u->first_x.x = j;
		u->first_x.y = i;
	}
	if ((tab[i][j] == 'O' || tab[i][j] == 'o') && u->first_o_on == 0)
	{
		u->first_o_on = 1;
		u->first_o.x = j;
		u->first_o.y = i;
	}
	if (tab[i][j] == 'x' && u->last_played_x_on == 0)
	{
		u->last_played_x_on = 1;
		u->last_played_x.x = j;
		u->last_played_x.y = i;
	}
	if (tab[i][j] == 'o' && u->last_played_o_on == 0)
	{
		u->last_played_o_on = 1;
		u->last_played_o.x = j;
		u->last_played_o.y = i;
	}
}

void		analyse_tab(char **tab, t_struct *u)
{
	int i;
	int j;

	i = -1;
	while (++i < u->map_h)
	{
		j = -1;
		while (++j < u->map_w)
			first_and_last_map(tab, i, j, u);
	}
}
