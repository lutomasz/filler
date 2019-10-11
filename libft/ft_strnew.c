/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 16:46:59 by lutomasz          #+#    #+#             */
/*   Updated: 2018/10/05 16:47:18 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *tab;

	if ((tab = (char*)malloc(sizeof(char) * size + 1)) == NULL)
		return (NULL);
	ft_memset(tab, '\0', size + 1);
	return (tab);
}
