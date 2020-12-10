/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:58:10 by hroh              #+#    #+#             */
/*   Updated: 2020/10/08 16:12:33 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int val, size_t s)
{
	size_t			i;
	unsigned char	*d;

	i = 0;
	d = dest;
	while (i < s)
	{
		d[i] = val;
		i++;
	}
	return (dest);
}
