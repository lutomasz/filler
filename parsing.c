/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <lutomasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 02:19:49 by lutomasz          #+#    #+#             */
/*   Updated: 2019/10/14 13:39:11 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_struct *init_utils(char *map)
{
	t_struct *u;

	u = (t_struct*)malloc(sizeof(t_struct));
	u->fd = open(map, O_RDONLY);
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


	return (u);
}

void ft_get_size_map(t_struct *u)
{
	char *line ;
	int i;

	i = 0;
	if ((get_next_line(u->fd, &line)) == 1)
		//printf("%s\n", line);
	//line = strnstr(line, "Plateau", 10);
	// 	printf("=====%c======\n", *line);
	while ((*line >= 'a' && *line  <= 'z') || (*line == ' '))
	 	line++;
	u->map_w = ft_atoi(line);

	while (line[0] >= '0' && line[0] <= '9')
		line++;

	u->map_h = ft_atoi(line);

	// printf("x = %d\n", u->map_w);
	// printf("y = %d\n", u->map_h);

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

void analyse_tab(char **tab, t_struct *u)
{
	int i;
	int j;

	printf("%d\n",u->map_w);
	printf("%d\n",u->map_h);
	printf("\n");
	i = 0;
	while (i < u->map_h)
	{
		j = 0;
		while (j < u->map_w)
		{
			// printf("sadasasd\n");
			// if (tab[i][j] == 'X')
			// {
			// 	if (u->first_x_on == 0)
			// 	{
			// 		u->first_x_on = 1;
			// 		u->first_x.x = j;
			// 		u->first_x.y = i;
			// 	}
			// }
			printf("cpt ; %d\n", j);
			if (tab[i][j] == 'O')
			{
				// if (u->first_o_on == 0)
				// {
				// 	u->first_o_on = 1;
					u->first_o.x = j;
					u->first_o.y = i;
					printf("ok\n");
				// }
			}
			// if (tab[i][j] == 'x')
			// {
			// 	if (u->last_played_x_on == 0)
			// 	{
			// 		u->last_played_x_on = 0;
			// 		u->last_played_x.x = j;
			// 		u->last_played_x.y = i;
			// 	}
			// }
			// if (tab[i][j] == 'o')
			// {
			// 	if (u->last_played_o_on == 0)
			// 	{
			// 		u->last_played_o_on = 1;
			// 		u->last_played_o.x = j;
			// 		u->last_played_o.y = i;
			// 	}
			// }
			j++;
		}
		i++;
		printf("%d\n", i);

	}
printf("ok\n");
}



char **get_map(t_struct *u)
{
	char **tmp;
	int i;
	char *line;

	i = 0;
	tmp = (char**)malloc(sizeof(char*) * u->map_w + 1);
	get_next_line(u->fd, &line);
	free(line);
	while (i < u->map_w)
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

	// u->piece_h = 0;
	// u->piece_w = 0;
	// u->shift_gauche = 0;
	// u->shift_haut = 0;
	// u->shape = NULL;
	// u->tmp_shape = NULL;


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

	// printf("i = %d\n", i);
	// printf("j = %d\n", j);
	// printf("down h = %d\n", u->shift.down);
	// printf("right w = %d\n", u->shift.right);

	// printf("first h = %d\n", u->first_star_x);
	// printf("first w = %d\n", u->first_star_y);
	// printf("last h = %d\n", u->last_star_x);
	// printf("last w = %d\n", u->last_star_y);

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

void ft_swap(int *a, int *b)
{
	int tmp_a;

	tmp_a = *a;
	*a = *b;
	*b = tmp_a;
}

void get_piece(t_struct *u)
{
	char *line;
	int i;


	get_next_line(u->fd, &line);
	while (*line == '\0')
		get_next_line(u->fd, &line);
	line = ft_strchr(line, ' ');

	printf("%s\n", line);
	u->piece.h = ft_atoi(line);
	line++;

	while (line[0] >= '0' &&  line[0] <= '9')
		line++;

	u->piece.w = ft_atoi(line);
	i = 0;

	// printf("h = %d\n", u->piece_h);
	// printf("w = %d\n", u->piece_w);
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
	ft_swap(&u->map_w, &u->map_h);

}
