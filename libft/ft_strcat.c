/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 16:36:26 by lutomasz          #+#    #+#             */
/*   Updated: 2018/10/05 16:36:53 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	char			*c2;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	c2 = (char*)s2;
	while (s1[i])
		i++;
	while (c2[j])
	{
		s1[i + j] = c2[j];
		j++;
	}
	s1[i + j] = '\0';
	return (s1);
}
