/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:30:03 by hroh              #+#    #+#             */
/*   Updated: 2020/10/12 15:28:29 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(int n)
{
	int len;

	len = (n <= 0) ? 1 : 0;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	char			*re;
	unsigned int	us_n;
	int				sign;
	int				len;

	len = get_len(n);
	if (!(re = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	sign = (n < 0) ? -1 : 1;
	us_n = (n < 0) ? -1 * n : n;
	re[len] = 0;
	len--;
	while (len >= 0)
	{
		re[len] = '0' + (us_n % 10);
		us_n = us_n / 10;
		len--;
	}
	if (sign == -1)
		re[0] = '-';
	return (re);
}
