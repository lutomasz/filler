/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <lutomasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 20:04:39 by lutomasz          #+#    #+#             */
/*   Updated: 2019/11/18 18:02:02 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		find_smallest_val(t_struct *u, int iter)
{
	int min;
	int i;
	int j;

	min = INT_MAX;
	i = (u->possible_pos[iter][1] - 1 >= 0) ? u->possible_pos[iter][1] - 1 : 0;
	while (i <= u->possible_pos[iter][1] + 1 && i < u->map_h)
	{
		j = (u->possible_pos[iter][0] - 1 >= 0) ? u->possible_pos[iter][0] - 1 : 0;
		while (j <= u->possible_pos[iter][0] + 1 && j < u->map_w)
		{
			if (!is_me(u, u->map[i][j]))
				min = (u->h_map[i][j] < min && u->h_map[i][j] != 0) ? u->h_map[i][j] : min;
			++j;
		}
		i++;
	}
	u->min_dist_adj = (min < u->min_dist_adj) ? min : u->min_dist_adj;
	return (min);
}

int		set_my_pos(t_struct *u)
{
	int i;
	int j;
	int found;
	int iter;

	iter = 0;
	found = 0;
	i = (u->my_c[0] == 'o') ? u->first_o.y - 1 : u->first_x.y - 1;
	while (++i < u->map_h)
	{
		j = -1;
		found = 0;
		while (++j < u->map_w)
		{
			if (is_me(u, u->map[i][j]) && ++found)
			{
				u->possible_pos[iter][0] = j;
				u->possible_pos[iter++][1] = i;
				u->possible_pos[iter - 1][2] = find_smallest_val(u, iter - 1);
			}
		}
		if (found == 0)
			break ;
	}
	return (iter);
}

int		trim_pos(t_struct *u)
{
	int i;
	int j;
	int min;

	if (!(u->trimmed_pos = malloc_2d_int_arr(u->trimmed_pos, u->num_me, 2)))
		return (-1);
	min = INT_MAX;
	i = -1;
	j = 0;
	i = -1;
	u->num_of_trims = u->num_me;
	while (++i < u->num_me)
	{
		if (u->possible_pos[i][2] == u->min_dist_adj)
		{
			u->trimmed_pos[j][0] = u->possible_pos[i][0];
			u->trimmed_pos[j][1] = u->possible_pos[i][1];
			u->trimmed_pos[j++][2] = u->possible_pos[i][2];
		}
	}
	return (j);
}

void		free_str2(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void		free_double_int(int **str, int elements)
{
	int i;

	i = -1;
	while (++i < elements && str[i])
   		free(str[i]);
	free(str);
}

void	free_all(t_struct *u)
{
	// free(u->h_map);
	if (u->smallest_val != 0)
		free(u->smallest_val);
	//free int **
	// free_tab((void**)u->h_map);
	free_double_int(u->h_map, u->map_h);
	//free_tab((void**)u->piece.coord);
	free_double_int(u->piece.coord, u->piece.total);
	//free_tab((void**)u->trimmed_pos);
	free_double_int(u->trimmed_pos, u->num_of_trims);
	//free(u->trimmed_pos);
	//free char**
	free_str2(u->tmp_shape);
	free_str2(u->shape);
	free_str2(u->map);

}

int init_parse(t_struct *u, char *av)
{
	if (init_utils(u, av) == -1)
	{
		printf("ERROR INIT\n");
		return (-1);
	}
	if ((ft_get_size_map(u)) == -1)
	{
		printf("map_error\n");

		return (-1); //print error //read only once
	}
	//printf("here\n");
	if (!(u->map = get_map(u)))
	{
		printf("map_error\n");
		return (-1);
	}
	//u->symbol = 'x';  // X = x + 32
	if (!(get_piece(u)))
	{
		free_all(u);
		printf("map_error\n");
		return (-1);
	}
	return (1);
}

/*
** main with infinite loop
*/

/*
** main with infinite loop
*/

int		main(int argc, char **argv)
{
	t_struct u;

	// while (1)
	// {
		if (init_parse(&u, argv[1]) == -1)
		{
			printf("error parse\n");
			return (-1);
		}
		set_me_his(&u);
			//ft_print_tab2(u.map);
		set_players_pos(&u);
		//print_int2(u.h_map, u.map_w, u.map_h);
		//u.player1 = 1;		// REMOVE
		//printf("%d\n", u.player1);
		// set_me_his(&u);
		// //ft_print_tab2(u.map);
		// set_players_pos(&u);
		//ft_print_tab2(u.map);
		//print_int2(u.h_map, u.map_w, u.map_h);
		u.map = get_heatmap(&u);
	//printf("ok\n");
		//ft_print_tab2(u.map);
		u.num_me = set_my_pos(&u);
		u.num_me = trim_pos(&u);
		if (u.piece.total > 0)
			ft_print_tab2(u.shape);;
		select_pos(&u);
		printf("ok\n");
		if (!(u.smallest_val = (int*)(malloc(sizeof(int) * u.num_me)))) // use index of smallest value to decide which piece overlaps
			return (-1);
		// other_place(&u);
		place_piece(&u);
		//free_all(&u);
	// }
	// printf("\n%s\n", "PIECE");

	// ft_print_tab2(u.tmp_shape);
	// printf("\n");

	// // printf("%s\n", "SHAPE");
	// if (u.piece.total > 0)
	// 	ft_print_tab2(u.shape);;

	// print_int2(u.h_map, u.map_w, u.map_h);

// =======
// 		if (u.piece.total > 0)
// 			ft_print_tab2(u.shape);;
// 		printf("ok\n");
// 		select_pos(&u);
// 		if (!(u.smallest_val = (int*)(malloc(sizeof(int) * u.num_me)))) // use index of smallest value to decide which piece overlaps
// 			return (-1);
// 		place_piece(&u);
// 	}
// 	else
// 	{
// 		printf("wrong number of params\n");
// 		return (0);
// 	}
// 	ft_print_tab2(u.tmp_shape);
// 	printf("\n");
// >>>>>>> 496a58a0099eb210a51994fcfabb0bd1a9d52a7a

	return (0);
	//ft_print_tab2(u->map);
}

/*
** old main for debugging
*/

// int		main(int argc, char **argv)
// {
// 	t_struct u;

// 	if (argc == 2)
// 	{
// 		if (init_parse(&u, argv[1]) == -1)
// 		{
// 			printf("error parse\n");
// 			return (-1);
// 		}
// 		//u.player1 = 1;		// REMOVE
// 		set_me_his(&u);
// 		set_players_pos(&u);
// 		u.map = get_heatmap(&u);
// 		u.num_me = set_my_pos(&u);
// 		if (!(u.num_me = trim_pos(&u)))
// 		{
// 			free_all(&u);
// 			return (0);
// 		}
// 		select_pos(&u);
// 		if (!(u.smallest_val = (int*)(malloc(sizeof(int) * u.num_me)))) // use index of smallest value to decide which piece overlaps
// 		{
// 			free_all(&u);
// 			return (-1);
// 		}
// 		place_piece(&u);
// 		//printf("ok\n");
// 		free_all(&u);
// 		// printf("%d", 0);
// 		// printf(" ");
// 		// printf("%d", 0);
// 		// printf("\n");
// 		//printf("player = %d\n", u.player1);
// 		return (1);
// 	}
// 	else
// 	{
// 		printf("%d", 0);
// 		printf(" ");
// 		printf("%d", 0);
// 		printf("\n");
// 		//printf("wrong number of params\n");
// 		return (0);
// 	}
// 	ft_print_tab2(u.tmp_shape);
// 	printf("\n");
// 	if (u.piece.total > 0)
// 		ft_print_tab2(u.shape);;
// 	print_int2(u.h_map, u.map_w, u.map_h);
// 	free_all(&u);
// 	return (0);
// 	//ft_print_tab2(u->map);
// }
