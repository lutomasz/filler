/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 16:49:14 by lutomasz          #+#    #+#             */
/*   Updated: 2018/10/05 16:49:39 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*tab;
	unsigned int	i;
	unsigned char	*str;

	if (s == NULL || f == NULL)
		return (NULL);
	i = ft_strlen(s);
	str = (unsigned char*)s;
	if ((tab = (char*)malloc(sizeof(char) * i + 1)) == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		tab[i] = (*f)(str[i]);
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
