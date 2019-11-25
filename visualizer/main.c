/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 04:16:38 by skrabby           #+#    #+#             */
/*   Updated: 2019/11/15 10:40:49 by skrabby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "../filler.h"

char		*g_p1name;
char		*g_p2name;

char	*ft_strndup(const char *s1, size_t n)
{
	int		length;
	int		i;
	char	*temp;

	i = 0;
	if (ft_strlen(s1) >= n)
		length = n;
	else
		length = ft_strlen(s1);
	temp = (char*)malloc(sizeof(char) * (length + 1));
	if (!temp)
		return (0);
	while (s1[i] != '\0' && n > 0)
	{
		temp[i] = s1[i];
		i++;
		n--;
	}
	temp[i] = '\0';
	return (temp);
}

char	*ft_strupr(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		s[i] = ft_toupper(s[i]);
		i++;
	}
	return (s);
}

void		draw_players(t_vis *v, t_vm *map)
{
	char *s;
	char *score;

	score = ft_itoa(v->p1score);
	s = ft_strjoin("SCORE: ", score);
	mlx_string_put(v->mlx, v->win, (v->width / 2) - 30,
	(v->height / 10) - 20, 0x0FFFFFF, g_p1name);
	mlx_string_put(v->mlx, v->win, (v->width / 2) - 50,
	(v->height / 10) + 60, 0x0FFFFFF, s);
	mlx_string_put(v->mlx, v->win, (v->width / 2) - 30,
	(v->height - (v->height / 10)), 0x0FFFFFF, g_p2name);
	// free(score);
	// free(s);
	score = ft_itoa(v->p2score);
	s = ft_strjoin("SCORE: ", score);
	mlx_string_put(v->mlx, v->win, (v->width / 2) - 50,
	v->height - (v->height / 10) - 80, 0x0FFFFFF, s);
	// free(s);
	// free(score);
}

void		check_players(char *line, t_vm *map, int player)
{
	int begin;
	int i;

	begin = 0;
	i = 0;
	while (*line != '[')
		line++;
	line++;
	while (line[i] != '\0')
	{
		if (line[i] == '/')
			begin = i + 1;
		i++;
	}
	i = 0;
	while (line[i + begin] != '.')
		i++;
	if (player == 1)
		g_p1name = ft_strupr(ft_strndup(line + begin, i));
	else if (player == 2)
		g_p2name = ft_strupr(ft_strndup(line + begin, i));
}

static int	ft_loop(t_vis *v, t_vm *map)
{
	v->ret = mlx_get_data_addr(v->img, &(v->bits_per_pixel),
			&(v->size_line), &(v->endian));
	if (!v->first_parse)
		parse_data(v, map);
	draw_background(v);
	draw_pcolor(v, map);
	draw_map(v, map);
	draw_bars(v, map);
	mlx_put_image_to_window(v->mlx, v->win, v->img, 0, 0);
	mlx_destroy_image(v->mlx, v->img);
	v->img = mlx_new_image(v->mlx, v->width, v->height);
	draw_players(v, map);
	draw_gameover(v);
	v->first_parse = 0;
	return (0);
}

int			main(void)
{
	t_vis	*v;
	t_vm	*map;

	if (!(v = (t_vis*)malloc(sizeof(t_vis))) ||
			!(map = (t_vm*)malloc(sizeof(t_vm))))
		exit(0);
	set_var(v, map);
	parse_data(v, map);
	v->map_created = 0;
	v->mlx = mlx_init();
	v->win = mlx_new_window(v->mlx, v->width, v->height, WINDOW_NAME);
	v->img = mlx_new_image(v->mlx, v->width, v->height);
	mlx_hook(v->win, 2, 2, keyboard, v);
	ft_loop(v, map);
	//free_vmap(v, map);
	mlx_loop_hook(v->mlx, ft_loop, v);
	mlx_loop(v->mlx);
	// free_vmap(v, map);
	// free(g_p1name);
	// free(g_p2name);
	//free(v);
	//free(map);
	return (0);
}
