/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 16:26:19 by lutomasz          #+#    #+#             */
/*   Updated: 2018/10/08 10:54:33 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*dest;
	unsigned int	i;

	i = 0;
	dest = (unsigned char*)b;
	while (len)
	{
		dest[i] = c;
		i++;
		len--;
	}
	return ((void*)b);
}
