/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 16:31:07 by lutomasz          #+#    #+#             */
/*   Updated: 2018/11/26 13:09:49 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char			*str;
	size_t			i;

	i = 0;
	str = (char*)s;
	while (n--)
	{
		if (str[i] == (char)c)
			return ((void*)str + i);
		i++;
	}
	return (NULL);
}
