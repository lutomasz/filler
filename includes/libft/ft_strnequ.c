/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 16:50:38 by lutomasz          #+#    #+#             */
/*   Updated: 2018/10/05 16:50:56 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t			i;
	unsigned char	*c1;
	unsigned char	*c2;

	c1 = (unsigned char*)s1;
	c2 = (unsigned char*)s2;
	i = 0;
	if (c1 != NULL && c2 != NULL)
	{
		while ((c1[i] && c1[i] == c2[i]) && i < n)
		{
			if ((c1[i] - c2[i]) != 0)
				return (0);
			i++;
		}
		if (c1[i] != c2[i] && i < n)
			return (0);
		return (1);
	}
	return (0);
}
