/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 16:51:57 by lutomasz          #+#    #+#             */
/*   Updated: 2018/11/26 12:56:12 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int x)
{
	return (x >= 0 ? x : -x);
}

static int	ft_get_end(char const *s, int i)
{
	while (s[i])
		i++;
	i--;
	while (((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && (i >= 0)))
		i--;
	i++;
	return (i);
}

char		*ft_strtrim(char const *s)
{
	char	*tab;
	int		start;
	int		end;
	int		i;

	if (s != NULL)
	{
		i = 0;
		while (((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && (s[i])))
			i++;
		start = i;
		end = ft_get_end(s, i);
		if ((tab = (char*)malloc(sizeof(char) * (ft_abs(end - start + 1))))
			== NULL)
			return (NULL);
		i = 0;
		while (s[start] && start < end)
			tab[i++] = s[start++];
		tab[i] = '\0';
		return (tab);
	}
	return (NULL);
}
