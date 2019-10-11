/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 16:46:02 by lutomasz          #+#    #+#             */
/*   Updated: 2018/10/05 16:46:24 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *tab;

	tab = NULL;
	if (size > 0)
	{
		if ((tab = (void*)malloc(sizeof(void) * size)) == NULL)
			return (NULL);
		ft_bzero(tab, size);
		return (tab);
	}
	return (tab);
}
