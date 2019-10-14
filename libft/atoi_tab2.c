/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_tab2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:40:53 by lutomasz          #+#    #+#             */
/*   Updated: 2019/10/14 17:41:06 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int **ft_copy_values(char **tab_char, int **tab_int)
{
	size_t i;
 	size_t j_char;
	size_t j_int;

	i = 0;
	while (tab_char[i])
	{
		j_char = 0;
		j_int = 0;
		while (tab_char[i][j_char])
		{
			tab_int[i][j_int] = ft_atoi(&tab_char[i][j_char]);

			while (tab_char[i][j_char] != ' ' && tab_char[i][j_char] != '\0')
				j_char++;
			if (tab_char[i][j_char] == ' ')
			{
				while (tab_char[i][j_char] == ' ' && tab_char[i][j_char])
					j_char++;
			}
			j_int++;
		}
		i++;
	}
	return (tab_int);
}

static void	free_tab(void **tab, int i, int which_one)
{
	if (which_one == 1)
	{
		while(i-- >= 0)
			free(tab[i]);
		tab = NULL;
	}
	else
	{
		while(*tab)
		{
			free(*tab);
			tab++;
		}
		tab = NULL;
	}
}

int 		**atoi_tab2(char **tab_char, int w, int h)
{
	int **tab_int;
	int i;

	if (!(tab_int = (int**)malloc(sizeof(int*) * h)))
		return (NULL);
	i = 0;
	while (i < h + 1)
	{
		if (!(tab_int[i] = (int*)malloc(sizeof(int) * w)))
			return (NULL);
		i++;
	}
	if (!(tab_int = ft_copy_values(tab_char, tab_int)))
		return (NULL);
	free_tab((void**)tab_char, 0, 0);
	return (tab_int);
}