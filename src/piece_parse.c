/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <lutomasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:02:11 by lutomasz          #+#    #+#             */
/*   Updated: 2019/11/20 15:55:34 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**	get coordonates of every star of the piece and put in into a int[][] array
**	will be useful for placing.
*/

void		set_tab_int2_to_zero(int **map, int width, int height)
{
	int i;
	int j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
			map[i][j] = 0;
	}
}

int			get_coordonates(t_struct *u)
{
	int i;
	int x;
	int y;

	if (!(u->piece.coord = (int**)malloc(sizeof(int*) * u->piece.total)))
		return (0);
	i = 0;
	y = -1;
	while (u->tmp_shape[++y] && i < u->piece.total)
	{
		x = -1;
		while (u->tmp_shape[y][++x] && i < u->piece.total)
		{
			if (u->tmp_shape[y][x] == '*')
			{
				if (!(u->piece.coord[i] = (int*)malloc(sizeof(int) * (2))))
					return (free_double_int(u->piece.coord, i - 1));
				u->piece.coord[i][0] = x;
				u->piece.coord[i][1] = y;
				i++;
			}
		}
	}
	return (1);
}

/*
**	get data of the given piece
*/

void		first_and_last_piece(char **piece, t_struct *u)
{
	int i;
	int j;

	u->piece.first_y = u->piece.w;
	u->piece.first_x = u->piece.h;
	i = -1;
	while (piece[++i])
	{
		j = -1;
		while (piece[i][++j])
		{
			if (piece[i][j] == '*')
			{
				u->piece.total++;
				if (i < u->piece.first_x)
					u->piece.first_x = i;
				if (j < u->piece.first_y)
					u->piece.first_y = j;
				if (i > u->piece.last_x)
					u->piece.last_x = i;
				if (j > u->piece.last_y)
					u->piece.last_y = j;
			}
		}
	}
}

/*
**	read the piece and get their width and height
*/

int			get_piece_data(char *line, t_struct *u)
{
	char *ptr;

	get_next_line(u->fd, &line);
	while (*line == '\0')
	{
		free(line);
		get_next_line(u->fd, &line);
	}
	ptr = line;
	line = ft_strchr(line, ' ');
	u->piece.h = ft_atoi(line);
	line++;
	while (line[0] >= '0' && line[0] <= '9')
		line++;
	u->piece.w = ft_atoi(line);
	free(ptr);
	return (1);
}

/*
**	get the piece from imput into a new tab && store it in our structure
*/

int			get_piece(t_struct *u)
{
	char	*line;
	int		i;

	line = NULL;
	get_piece_data(line, u);
	if (!(u->tmp_shape = (char**)malloc(sizeof(char*) * u->piece.h + 1)))
		return (0);
	i = 0;
	while (i < u->piece.h)
	{
		get_next_line(u->fd, &line);
		if (!(u->tmp_shape[i] = ft_strsub(line, 0, u->piece.w)))
		{
			free(line);
			return (free_unset_tab(u->tmp_shape, i - 1, 0));
		}
		i++;
		free(line);
	}
	u->tmp_shape[i] = 0;
	first_and_last_piece(u->tmp_shape, u);
	get_coordonates(u);
	if (u->piece.coord == 0)
		return (-1);
	return (1);
}
