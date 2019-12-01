/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 16:29:09 by lutomasz          #+#    #+#             */
/*   Updated: 2018/11/30 15:36:16 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;
	size_t			i;

	i = 0;
	c1 = (unsigned char*)dst;
	c2 = (unsigned char*)src;
	while (n--)
	{
		c1[i] = c2[i];
		if (c2[i] == (unsigned char)c)
			return ((void*)c1 + i + 1);
		i++;
	}
	return (NULL);
}
