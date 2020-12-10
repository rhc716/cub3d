/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 16:30:34 by hroh              #+#    #+#             */
/*   Updated: 2020/10/09 12:12:10 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	uc;

	i = 0;
	s = (unsigned char *)src;
	uc = (unsigned char)c;
	while (i < n)
	{
		if (s[i] == uc)
		{
			return (&s[i]);
		}
		i++;
	}
	return (0);
}
