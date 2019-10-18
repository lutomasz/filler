/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab2_cpy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:07:17 by lutomasz          #+#    #+#             */
/*   Updated: 2019/10/16 19:07:24 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char **tab2_cpy(char **src)
{
	int i;
	int len;
	char **tab;

	len = 0;
	while (src[len])
		len++;
	tab = (char**)malloc(sizeof(char*) * len + 1);
	i = -1;
	while (++i < len)
		tab[i] = ft_strdup(src[i]);
	tab[i] = 0;
	return (tab);
}
