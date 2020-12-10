/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 17:49:29 by hroh              #+#    #+#             */
/*   Updated: 2020/10/14 14:05:17 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new_first;
	t_list *curr_new;
	t_list *curr_old;

	if (lst == NULL)
		return (NULL);
	if (!(new_first = ft_lstnew(f(lst->content))))
		return (NULL);
	curr_new = new_first;
	curr_old = lst->next;
	while (curr_old != NULL)
	{
		if (!(curr_new->next = ft_lstnew(f(curr_old->content))))
		{
			ft_lstclear(&new_first, del);
			return (NULL);
		}
		curr_new = curr_new->next;
		curr_old = curr_old->next;
	}
	return (new_first);
}
