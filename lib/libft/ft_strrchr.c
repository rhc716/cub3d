/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 03:55:22 by hroh              #+#    #+#             */
/*   Updated: 2020/10/09 13:10:29 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t s;

	s = ft_strlen(str);
	while (s > 0)
	{
		if (str[s] == c)
		{
			return ((char *)str + s);
		}
		s--;
	}
	if (str[s] == c)
		return ((char *)str + s);
	return (0);
}
