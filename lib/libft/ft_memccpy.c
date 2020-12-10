/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:24:34 by hroh              #+#    #+#             */
/*   Updated: 2020/10/14 14:22:20 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;
	unsigned char	uc;

	i = 0;
	d = dest;
	s = (unsigned char *)src;
	uc = c;
	while (i < n)
	{
		d[i] = s[i];
		if (s[i] == uc)
		{
			return (dest + i + 1);
		}
		i++;
	}
	return (0);
}
