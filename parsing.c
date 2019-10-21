/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <lutomasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 02:19:49 by lutomasz          #+#    #+#             */
/*   Updated: 2019/10/18 16:56:35 by spozzi           ###   ########.fr       */
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
	u->coord = NULL;
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
<<<<<<< HEAD
	//others
	u->player = 0;
=======

	u->player1 = -1;
>>>>>>> 48efa37998709c131e8a8dfd2e1a43c1cd5db813
	u->en = NULL;
	u->me = NULL;
	u->map_cpy = NULL;
	return (u);
}

/*
*** print an error message when wrong imput
*/

void		usage(void)
{
	ft_putendl("insert correct map");
}

/*
**	get_data from imput
** 	if first round, get the player number
**	the fonction stops when "plateau" is found or end of file
*/

int			read_map_data(char *line, t_struct *u)
{
<<<<<<< HEAD
	if (ft_strncmp(line, "Plateau", 6) == 0 ||
		ft_strncmp(line, "plateau", 6) == 0)
		return (0);
	else if (u->player == 0 && ft_strncmp(line, "$$$", 2) == 0)
	{
		if (ft_strstr(line, "p2"))
			u->player = 2;
		if (ft_strstr(line, "p1"))
			u->player = 1;
		free(line);
=======
	if (u->player1 == 1)
	{
		u->en = "Xx";
		u->me = "Oo";
	}
	if (u->player1 == 0)
	{
		u->en = "Oo";
		u->me = "Xx";
>>>>>>> 48efa37998709c131e8a8dfd2e1a43c1cd5db813
	}
	else
		free(line);
	return (1);
}

/*
**	get map hight and width from the line containing "plateau"
*/

void		get_width_height_map(char *line, t_struct *u)
{
	int i;

	i = 0;
	while ((line[i] >= 'a' && line[i] <= 'z') ||
		(line[i] >= 'A' && line[i] <= 'Z') || (line[i] == ' '))
		i++;
	u->map_h = ft_atoi(line + i);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	u->map_w = ft_atoi(line + i);
}

int			ft_get_size_map(t_struct *u)
{
	char	*line;

	while ((get_next_line(u->fd, &line)))
	{
		if (*line < 1)
		{
			usage();
			return (-1);
<<<<<<< HEAD
=======
		}
		if (ft_strncmp(line, "Plateau", 6) == 0 || ft_strncmp(line, "plateau", 6) == 0)
			break ;
		else if (u->player1 == -1 && ft_strncmp(line, "$$$", 2) == 0)
		{
			if (ft_strstr(line, "p1"))
			u->player1 = 1;
			if (ft_strstr(line, "p2"))
				u->player1 = 0;
			wich_player(u);
			free(line);
>>>>>>> 48efa37998709c131e8a8dfd2e1a43c1cd5db813
		}
		if (read_map_data(line, u) == 0)
			break ;
	}
	if (!(ft_strncmp(line, "Plateau", 6) == 0) &&
		!(ft_strncmp(line, "plateau", 6) == 0))
		return (-1);
	get_width_height_map(line, u);
	if (*line)
		free(line);
	return (1);
}

/*
**	copy line from imput to the new tab
*/

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
	if (tab[i][j] == 'O' && u->first_x_on == 0)
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

/*
**	if the read is correct then get copy each line into a new tab &&
**	send it to the analyse fonction
*/

char		**get_map(t_struct *u)
{
	char	**tmp;
	int		i;
	char	*line;

	if (u->map_h != 0 && u->map_w != 0)
		if (!(tmp = (char**)malloc(sizeof(char*) * u->map_h + 1)))
			return (NULL);
	get_next_line(u->fd, &line);
	free(line);
	i = 0;
	while (i < u->map_h)
	{
		get_next_line(u->fd, &line);
		if (!(tmp[i] = copy_line(line)))
			return (NULL);
		free(line);
		i++;
	}
	tmp[i] = 0;
	analyse_tab(tmp, u);
	//u->map_cpy = tab2_cpy(tmp);
	return (tmp);
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
				return (-1);
			i++;
		}
		u->shape[i] = 0;
	}
	return (1);
}

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
					return (0);
				coord[i][0] = y;
				coord[i][1] = x;
				i++;
			}
		}
	}
	return (coord);
}

/*
**	read the piece and get their width and height
*/

int			get_piece_data(char *line, t_struct *u)
{
	get_next_line(u->fd, &line);
	while (*line == '\0')
		get_next_line(u->fd, &line);
	line = ft_strchr(line, ' ');
	u->piece.h = ft_atoi(line);
	line++;
	while (line[0] >= '0' && line[0] <= '9')
		line++;
	u->piece.w = ft_atoi(line);
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
		if (!(u->tmp_shape[i] = ft_strsub(line, 0, u->piece.w)))
			return (0);
		i++;
		free(line);
	}
	u->tmp_shape[i] = 0;
	if (!(analyse_piece(u->tmp_shape, u)))
		return (-1);
	u->coord = get_coordonates(u);
	if (!(u->coord))
		return (-1);
	return (1);
}
