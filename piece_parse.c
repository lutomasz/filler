/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:02:11 by lutomasz          #+#    #+#             */
/*   Updated: 2019/11/06 14:02:12 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**	get coordonates of every star of the piece and put in into a int[][] array
*/

int			**get_coordonates(t_struct *u)
{
	int i;
	int x;
	int y;
	int **coord;

	if (!(coord = (int**)malloc(sizeof(int*) * u->piece.total)))
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
				if (!(coord[i] = (int*)malloc(sizeof(int) * (2))))
				{
					free_double_int(coord, i - 1);
					return (0);
				}
				coord[i][0] = x;
				coord[i][1] = y;
				i++;
			}
		}
	}
	return (coord);
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
**	get the 'shape' of the piece and all the shifts to work with.
*/

int			analyse_piece(char **piece, t_struct *u)
{
	int i;

	first_and_last_piece(piece, u);
	u->shift.down = u->piece.h - 1 - u->piece.last_x;
	u->shift.right = u->piece.w - 1 - u->piece.last_y;
	u->shift.up = u->piece.first_x;
	u->shift.left = u->piece.first_y;
	if (u->piece.total > 0)
	{
		i = 0;
		if (!(u->shape = (char**)malloc(sizeof(char*) *
			(u->piece.h - u->shift.up + 1 - u->shift.down))))
			return (-1);
		while (i < u->piece.h - u->shift.up)
		{
			if (!(u->shape[i] = ft_strsub(u->tmp_shape[i + u->shift.up],
				u->shift.left, u->piece.w - u->shift.right)))
			{
				free_unset_tab(u->shape, i - 1);
				return (-1);
			}	
			i++;
		}
		u->shape[i] = 0;
	}
	return (1);
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

	get_piece_data(line, u);
	if (!(u->tmp_shape = (char**)malloc(sizeof(char*) * u->piece.h + 1)))
		return (0);
	i = 0;
	while (i < u->piece.h)
	{
		get_next_line(u->fd, &line);
		//printf("here\n");
		if (!(u->tmp_shape[i] = ft_strsub(line, 0, u->piece.w)))
		{
			free(line);
			free_unset_tab(u->tmp_shape, i - 1);
			return (0);
		}	
		i++;
		free(line);
	}
	u->tmp_shape[i] = 0;
	if (!(analyse_piece(u->tmp_shape, u)))
		return (-1);
	u->piece.coord = get_coordonates(u);
	if (u->piece.coord == 0)	
		return (-1);
	return (1);
}
