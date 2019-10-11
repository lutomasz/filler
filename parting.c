/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 02:19:49 by lutomasz          #+#    #+#             */
/*   Updated: 2019/03/12 02:20:01 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_struct *init_utils()
{
	t_struct *utils;
	
	utils = (t_struct*)malloc(sizeof(t_struct));
	utils->fd = open("exemple.txt", O_RDONLY);
	//map
	utils->map_x = 0;
	utils->map_y = 0;

	//positions
	utils->first_x_on = 0;
	utils->first_o_on = 0;
	utils->first_o.x = 0;
	utils->first_o.y = 0;
	utils->first_x.x = 0;
	utils->first_x.y = 0;

	utils->last_played_x_on = 0;
	utils->last_played_o_on = 0;
	utils->last_played_x.x = 0;
	utils->last_played_x.y = 0;
	utils->last_played_o.x = 0;
	utils->last_played_o.y = 0;

	//piece
	utils->shape = NULL;
	utils->tmp_shape = NULL;

	utils->shift.left = 0;
	utils->shift.up = 0;
	utils->shift.down = 0;
	utils->shift.right = 0;

	utils->piece.h = 0;
	utils->piece.w = 0;
	utils->piece.first_x = 0;
	utils->piece.first_y = 0;
	utils->piece.last_x = 0;
	utils->piece.last_y = 0;


	return (utils);
}

void ft_get_size_map(t_struct *utils)
{
	char *line ;
	int i;

	i = 0;
	if ((get_next_line(utils->fd, &line)) == 1)
		//printf("%s\n", line);
	// line = strnstr(line, "Plateau", 10);
	// 	printf("%c\n", *line);
	while ((*line >= 'a' && *line  <= 'z') || (*line == ' '))
	 	line++;
	utils->map_x = ft_atoi(line);

	while (line[0] >= '0' && line[0] <= '9')
		line++;

	utils->map_y = ft_atoi(line);

	// printf("x = %d\n", utils->map_x);
	// printf("y = %d\n", utils->map_y);

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
	tab = ft_strsub(str, s, i);
	return (tab);

}

void analyse_tab(char **tab, t_struct *utils)
{
	int i;
	int j;

	i = 0;
	while (tab[i] != '\0')
	{
		j = 0;
		while (tab[i][j] != '\0' && tab[i][j] != '\n')
		{
			if (tab[i][j] == 'X')
			{
				if (utils->first_x_on == 0)
				{
					utils->first_x_on = 1;
					utils->first_x.x = i;
					utils->first_x.y = j;
				}
			}
			if (tab[i][j] == 'O')
			{
				if (utils->first_o_on == 0)
				{
					utils->first_o_on = 1;
					utils->first_o.x = i;
					utils->first_o.y = j;
				}
			}
			if (tab[i][j] == 'x')
			{
				if (utils->last_played_x_on == 0)
				{
					utils->last_played_x_on = 0;
					utils->last_played_x.x = i;
					utils->last_played_x.y = j;
				}
			}
			if (tab[i][j] == 'o')
			{	
				if (utils->last_played_o_on == 0)
				{
					utils->last_played_o_on = 1;
					utils->last_played_o.x = i;
					utils->last_played_o.y = j;
				}
			}
			j++;
		}
		i++;
	}
}



char **get_tmp_map(t_struct *utils)
{
	char **tmp;
	int i;
	char *line;

	i = 0;
	tmp = (char**)malloc(sizeof(char*) * utils->map_x + 1);
	get_next_line(utils->fd, &line);
	free(line);
	while (i < utils->map_x)
	{
		get_next_line(utils->fd, &line);
		tmp[i] = copy_line(line);
		free(line);
		i++;
	}
	analyse_tab(tmp, utils);
	return (tmp);

}

	// utils->piece_h = 0;
	// utils->piece_w = 0;
	// utils->shift_gauche = 0;
	// utils->shift_haut = 0;
	// utils->shape = NULL;
	// utils->tmp_shape = NULL;


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

	// printf("i = %d\n", i);
	// printf("j = %d\n", j);
	// printf("down h = %d\n", u->shift.down);
	// printf("right w = %d\n", u->shift.right);

	// printf("first h = %d\n", u->first_star_x);
	// printf("first w = %d\n", u->first_star_y);
	// printf("last h = %d\n", u->last_star_x);
	// printf("last w = %d\n", u->last_star_y);
	
	i = 0;
	u->shape = (char**)malloc(sizeof(char*) * (u->piece.h - u->shift.up + 1 - u->shift.down));
	while (i < u->piece.h - u->shift.up)
	{
		u->shape[i] = ft_strsub(u->tmp_shape[i + u->shift.up], u->shift.left, u->piece.w - u->shift.right);
		i++;
	}
	u->shape[i] = 0;
	//ft_print_tab2(u->shape);
}

void ft_swap(int *a, int *b)
{
	int tmp_a;

	tmp_a = *a;
	*a = *b;
	*b = tmp_a;
}

void get_piece(t_struct *utils)
{
	char *line;
	int i;

	get_next_line(utils->fd, &line);

	line = ft_strchr(line, ' ');
	utils->piece.h = ft_atoi(line);
	line++;

	while (line[0] >= '0' &&  line[0] <= '9')
		line++;
	
	utils->piece.w = ft_atoi(line);
	i = 0;

	// printf("h = %d\n", utils->piece_h);
	// printf("w = %d\n", utils->piece_w);
	utils->tmp_shape = (char**)malloc(sizeof(char*) * utils->piece.h + 1);
	while (i < utils->piece.w)
	{
		get_next_line(utils->fd, &line);
		utils->tmp_shape[i] = ft_strsub(line, 0, utils->piece.w);
		i++;
	}
	utils->tmp_shape[i] = 0;
	analyse_piece(utils->tmp_shape, utils);
	ft_swap(&utils->map_x, &utils->map_y);
	
}
