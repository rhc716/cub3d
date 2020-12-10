/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 17:10:06 by hroh              #+#    #+#             */
/*   Updated: 2020/10/09 17:12:56 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *re;

	if (!(re = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	re->content = content;
	re->next = NULL;
	return (re);
}
