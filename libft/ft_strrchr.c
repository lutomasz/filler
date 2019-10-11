/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 16:38:43 by lutomasz          #+#    #+#             */
/*   Updated: 2018/10/05 16:39:02 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*str;
	unsigned int	i;
	char			*str1;

	str1 = NULL;
	str = (char*)s;
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			str1 = &str[i];
		i++;
	}
	if (str[i] == (char)c)
		str1 = &str[i];
	return (str1);
}
