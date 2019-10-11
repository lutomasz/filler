/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 16:27:22 by lutomasz          #+#    #+#             */
/*   Updated: 2018/10/08 11:07:52 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*tab;
	size_t			i;

	i = 0;
	tab = (unsigned char*)s;
	while (i < n)
	{
		tab[i] = 0;
		i++;
	}
}
