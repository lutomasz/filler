/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 16:55:07 by lutomasz          #+#    #+#             */
/*   Updated: 2018/10/05 16:55:54 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*tab;
	size_t	len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_intlen(n) + 1;
	if ((tab = (char*)malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	if (n == 0)
		tab[0] = '0';
	if (n < 0)
	{
		tab[0] = '-';
		n = -n;
	}
	tab[len - 1] = '\0';
	while (n)
	{
		len--;
		tab[len - 1] = (n % 10) + '0';
		n /= 10;
	}
	return (tab);
}
