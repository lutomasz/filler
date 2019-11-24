/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <lutomasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:57:26 by lutomasz          #+#    #+#             */
/*   Updated: 2019/11/20 16:33:02 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**	get_data from imput
** 	if first round, get the player number
**	the fonction stops when "plateau" is found or end of file
*/

int			read_map_data(char *line, t_struct *u, int *i)
{
	if (ft_strncmp(line, "Plateau", 6) == 0 ||
		ft_strncmp(line, "plateau", 6) == 0)
		return (0);
	else if (u->player1 == -1 && ft_strncmp(line, "$$$", 2) == 0)
	{
		if (ft_strstr(line, "p1"))
		{
			*i = 1;
			//u->player1 = 1;
		}
		if (ft_strstr(line, "p2"))
		{
			*i = 0;
			//u->player1 = 0;
		}
		free(line);
	}
	else
		free(line);
	return (1);
}

// int			read_map_data(char *line, t_struct *u)
// {
// 	if (ft_strncmp(line, "Plateau", 6) == 0 ||
// 		ft_strncmp(line, "plateau", 6) == 0)
// 		return (0);
// 	else if (u->player1 == -1 && ft_strncmp(line, "$$$", 2) == 0)
// 	{
// 		if (ft_strstr(line, "p1"))
// 		{
// 			if (ft_strstr(line, "filler.lupozzi"))
// 			{
// 				printf("check\n");
// 				u->player1 = 1;
// 			}
// 			else
// 			{
// 				printf("fcnooooooooooo\n");
// 				u->player1 = 0;
// 			}
// 		}
// 		// if (ft_strstr(line, "p2"))
// 		// {
// 		// 	printf("fnooooooooo\n");
// 		// 	u->player1 = 0;
// 		// }
// 		free(line);
// 	}
// 	else
// 		free(line);
// 	return (1);
// }

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

int			ft_get_size_map(t_struct *u, int *i)
{
	char	*line;

	while ((get_next_line(u->fd, &line) > 0))
	{
		if (*line < 1)
		{
			usage();
			return (-1);
		}
		if (read_map_data(line, u, i) == 0)
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

void set_tab_int2_to_zero(int **map, int width, int height)
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

int			**map_cpy_int(char **map, int width, int height)
{
	int	**h_map;
	int	i;

	if (map)
	{
		if (!(h_map = (int**)malloc(sizeof(int*) * height)))
			return (0);
		i = -1;
		while (++i < height)
		{
			if (!(h_map[i] = (int*)malloc(sizeof(int) * width)))
			{
				free_double_int(h_map, i - 1);
				return (0);
			}
		}
		set_tab_int2_to_zero(h_map, width, height);
		return (h_map);
	}
	return (0);
}

/*
**	if the read is correct then get copy each line into a new tab &&
**	send it to the analyse fonction
*/

void		free_unset_tab(char **str, int cnt)
{
	int i;

	i = -1;
	while (++i < cnt - 1)
		free(str[i]);
	free(str);
}

int		get_map(t_struct *u)
{
	// char	**tmp;
	int		i;
	char	*line;

	if (u->map_h != 0 && u->map_w != 0)
		if (!(u->map = (char**)malloc(sizeof(char*) * u->map_h + 1)))
			return (0);
	get_next_line(u->fd, &line);
	//printf("here\n");
	free(line);
	i = 0;
	while (i < u->map_h)
	{
		get_next_line(u->fd, &line);
		if (!(u->map[i] = copy_line(line)))
		{
			free(line);
			free_unset_tab(u->map, i - 1);
			return (0);
		}
		free(line);
		i++;
	}
	u->map[i] = 0;
	//ft_print_tab2(u->map);
	analyse_tab(u->map, u);
	u->h_map = map_cpy_int(u->map, u->map_w, u->map_h);
	if (u->h_map == 0)
		free_str2(u->map);
	return (1);
}
