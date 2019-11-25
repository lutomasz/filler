/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 10:35:33 by skrabby           #+#    #+#             */
/*   Updated: 2019/11/15 10:42:47 by skrabby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	save_map(char *line, t_vm *map)
{
	char	*begin;
	int		y;

	y = 0;
	while (y < map->sizey)
	{
		get_next_line(0, &line);
		begin = line;
		while (*line != ' ')
			line++;
		line++;
		map->arr[y] = ft_strdup(line);
	//	free(begin);
		y++;
	}
}

static void	get_visual_map(char *line, t_vis *v, t_vm *map)
{
	while (!(*line >= '0' && *line <= '9'))
		line++;
	map->sizey = ft_atoi(line);
	while (*line != ' ')
		line++;
	map->sizex = ft_atoi(line);
	if (map->setwh == 0)
		set_height_width(v, map);
	get_next_line(0, &line);
	//free(line);
	if (!(map->arr = (char**)malloc(sizeof(char*) * map->sizey)))
		exit(0);
	save_map(line, map);
}

void		free_vmap(t_vis *v, t_vm *map)
{
	int y;

	y = 0;
	while (y < map->sizey)
	{
		//free(map->arr[y]);
		y++;
	}
	free(map->arr);
	v->map_created = 0;
}

static void	handle_vmap(char *line, t_vis *v, t_vm *map)
{
	//if (v->map_created && !v->game_over)
	//	free_vmap(v, map);
	get_visual_map(line, v, map);
	v->map_created = 1;
}

void		parse_data(t_vis *v, t_vm *map)
{
	char *line;
	char *begin;

	while (1)
	{
		get_next_line(0, &line);
		begin = line;
		if (line[0] == '$' && line[10] == '1')
			check_players(line, map, 1);
		else if (line[0] == '$' && line[10] == '2')
			check_players(line, map, 2);
		else if (line[0] == 'P' && line[1] == 'l')
			handle_vmap(line, v, map);
		else if (line[0] == 'P' && line[1] == 'i')
			break ;
		else if (line[0] == '\0')
		{
			v->game_over = 1;
			break ;
		}
		//free(begin);
	}
	//free(begin);
}
