/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <lutomasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 02:19:49 by lutomasz          #+#    #+#             */
/*   Updated: 2019/12/01 17:39:42 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			init_utils(t_struct *u)
{
	u->fd = 0;
	u->map_w = 0;
	u->map_h = 0;
	u->first_x_on = 0;
	u->first_o_on = 0;
	u->first_o.x = -100;
	u->first_o.y = -100;
	u->first_x.x = -100;
	u->first_x.y = -100;
	u->last_played_x_on = 0;
	u->last_played_o_on = 0;
	u->last_played_x.x = -100;
	u->last_played_x.y = -100;
	u->last_played_o.x = -100;
	u->last_played_o.y = -100;
	u->tmp_shape = NULL;
	u->piece.coord = NULL;
	u->smallest_val = 0;
	u->bst_i = 0;
	u->ret = 0;
	init2(u);
	return (1);
}

void		init2(t_struct *u)
{
	u->piece.h = 0;
	u->piece.w = 0;
	u->piece.first_x = -100;
	u->piece.first_y = -100;
	u->piece.last_x = -100;
	u->piece.last_y = -100;
	u->piece.total = 0;
	u->player1 = -1;
	u->min_dist_adj = INT_MAX;
	u->curr_piece_fulcrum = 0;
	u->sam = 0;
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
