/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 14:43:48 by hroh              #+#    #+#             */
/*   Updated: 2020/10/14 14:28:27 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t s;
	size_t src_len;

	s = 0;
	if (!dest || !src)
		return (0);
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	while (src[s] && s < size - 1)
	{
		dest[s] = src[s];
		s++;
	}
	dest[s] = 0;
	return (src_len);
}
