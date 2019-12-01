/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 17:05:56 by lutomasz          #+#    #+#             */
/*   Updated: 2018/10/05 17:06:28 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *tmp;
	t_list *stock;

	if (!lst || (!(f)))
		return (NULL);
	tmp = f(lst);
	new = tmp;
	stock = NULL;
	while (lst->next)
	{
		lst = lst->next;
		if (!(tmp->next = f(lst)))
		{
			while (new)
			{
				stock = new->next;
				free(new);
				new = stock;
			}
			return (NULL);
		}
		tmp = tmp->next;
	}
	return (new);
}
