/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <lutomasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:44:08 by lutomasz          #+#    #+#             */
/*   Updated: 2019/10/23 13:10:06 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_int2(int **tab, int w, int h)
{
	int x;
	int y;

	x = 0;
	while (x < h)
	{
		y = 0;
		while (y < w)
		{
			ft_putnbr(tab[x][y]);
			ft_putchar('\t');
			y++;
		}
		ft_putchar('\n');
		x++;
	}
}
