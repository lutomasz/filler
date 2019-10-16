/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <lutomasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 02:19:49 by lutomasz          #+#    #+#             */
/*   Updated: 2019/10/14 16:13:36 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_struct *init_utils(char *map)
{
	t_struct *u;

	if (!(u = (t_struct*)malloc(sizeof(t_struct))) || (u->fd = open(map, O_RDONLY)) < 0)
		return (NULL);
	//map
	u->map_w = 0;
	u->map_h = 0;

	//positions
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

	//piece
	u->shape = NULL;
	u->tmp_shape = NULL;
	u->coord = NULL;

	u->shift.left = 0;
	u->shift.up = 0;
	u->shift.down = 0;
	u->shift.right = 0;

	u->piece.h = 0;
	u->piece.w = 0;
	u->piece.first_x = -100;
	u->piece.first_y = -100;
	u->piece.last_x = -100;
	u->piece.last_y = -100;
	u->piece.total = 0;

	u->player = 0;
	u->en = NULL;
	u->me = NULL;


	return (u);
}

void	wich_player(t_struct *u)
{
	if (u->player == 1)
	{
		u->en = "Xx";
		u->me = "Oo";
	}
	if (u->player == 2)
	{
		u->en = "Oo";
		u->me = "Xx";
	}
}

int ft_get_size_map(t_struct *u)
{
	char *line ;
	int i;

	i = 0;
	while ((get_next_line(u->fd, &line)) == 1)
	{
		if (ft_strncmp(line, "Plateau", 6) == 0 || ft_strncmp(line, "plateau", 6) == 0)
			break ;
		else if (u->player == 0 && ft_strncmp(line, "$$$", 2) == 0)
		{
			if (ft_strstr(line, "p2"))
				u->player = 2;
			if (ft_strstr(line, "p1"))
				u->player = 1;
			wich_player(u);
			free(line);
		}
		else
			free(line);
	}
	if (!(ft_strncmp(line, "Plateau", 6) == 0) && !(ft_strncmp(line, "plateau", 6) == 0))
		return (-1);
	while ((line[i] >= 'a' && line[i]  <= 'z') || (line[i] >= 'A' && line[i]  <= 'Z') || (line[i] == ' '))
	 	i++;
	u->map_h = ft_atoi(line + i);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	u->map_w = ft_atoi(line + i);
	if (*line)
		free(line);
	return (1);
}

char *copy_line(char *str)
{
	int i;
	int s;
	char *tab;

	i = 0;
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

void analyse_tab(char **tab, t_struct *u)
{
	int i;
	int j;

	i = 0;
	while (i < u->map_h)
	{
		j = 0;
		while (j < u->map_w)
		{
			if (tab[i][j] == 'X')
			{
				if (u->first_x_on == 0)
				{
					u->first_x_on = 1;
					u->first_x.x = j;
					u->first_x.y = i;
				}
			}
			if (tab[i][j] == 'O')
			{
				if (u->first_o_on == 0)
				{
					u->first_o_on = 1;
					u->first_o.x = j;
					u->first_o.y = i;
				}
			}
			if (tab[i][j] == 'x')
			{
				if (u->last_played_x_on == 0)
				{
					u->last_played_x_on = 0;
					u->last_played_x.x = j;
					u->last_played_x.y = i;
				}
			}
			if (tab[i][j] == 'o')
			{
				if (u->last_played_o_on == 0)
				{
					u->last_played_o_on = 1;
					u->last_played_o.x = j;
					u->last_played_o.y = i;
				}
			}
			j++;
		}
		i++;
	}
}


char **get_map(t_struct *u)
{
	char **tmp;
	int i;
	char *line;

	i = 0;
	if (u->map_h != 0 && u->map_w != 0)
		if(!(tmp = (char**)malloc(sizeof(char*) * u->map_h + 1)))
			return (NULL);
	get_next_line(u->fd, &line);
	free(line);
	while (i < u->map_h)
	{
		get_next_line(u->fd, &line);
		tmp[i] = copy_line(line);
		free(line);
		i++;
	}
	tmp[i] = 0;
	analyse_tab(tmp, u);
	return (tmp);

}

void analyse_piece(char **piece, t_struct *u)
{
	int i;
	int j;

	u->piece.first_y = u->piece.w;
	u->piece.first_x = u->piece.h;
	i = 0;
	while (piece[i])
	{
		j = 0;
		while (piece[i][j])
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
			j++;
		}
		i++;
	}
	u->shift.down = i - 1 - u->piece.last_x;
	u->shift.right = u->piece.w - 1 - u->piece.last_y;
	u->shift.up = u->piece.first_x;
	u->shift.left = u->piece.first_y;

	if (u->piece.total > 0)
	{
		i = 0;
		u->shape = (char**)malloc(sizeof(char*) * (u->piece.h - u->shift.up + 1 - u->shift.down));
		while (i < u->piece.h - u->shift.up)
		{
			u->shape[i] = ft_strsub(u->tmp_shape[i + u->shift.up], u->shift.left, u->piece.w - u->shift.right);
			i++;
		}
		u->shape[i] = 0;
	}
	//ft_print_tab2(u->shape);
}

int **get_coordonates(t_struct *u)
{
	int i;
	int x;
	int y;
	int **coord;

	i = 0;
	y = 0;
	coord = (int**)malloc(sizeof(int*) * u->piece.total);
	while (u->tmp_shape[y] && i < u->piece.total)
	{
		x = 0;
		while (u->tmp_shape[y][x] && i < u->piece.total)
		{
			if (u->tmp_shape[y][x] == '*')
			{
				coord[i] = (int*)malloc(sizeof(int) * (2));
				coord[i][0] = y;
				coord[i][1] = x;
				i++;
			}
			x++;
		}
		y++;
	}
	return (coord);
}

void get_piece(t_struct *u)
{
	char *line;
	int i;

	get_next_line(u->fd, &line);
	while (*line == '\0')
		get_next_line(u->fd, &line);
	line = ft_strchr(line, ' ');
	u->piece.h = ft_atoi(line);
	line++;

	while (line[0] >= '0' &&  line[0] <= '9')
		line++;

	u->piece.w = ft_atoi(line);
	i = 0;

	u->tmp_shape = (char**)malloc(sizeof(char*) * u->piece.h + 1);
	while (i < u->piece.w)
	{
		get_next_line(u->fd, &line);
		u->tmp_shape[i] = ft_strsub(line, 0, u->piece.w);
		i++;
	}
	u->tmp_shape[i] = 0;
	analyse_piece(u->tmp_shape, u);
	u->coord = get_coordonates(u);
	// ft_swap(&u->map_w, &u->map_h);

}
