/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 23:17:04 by hroh              #+#    #+#             */
/*   Updated: 2020/10/19 16:31:10 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	sign;
	long	re;

	i = 0;
	sign = 1;
	re = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		re = re * 10 + str[i] - '0';
		if (re > 2147483647 && sign == 1)
			return (-1);
		if (re > 2147483648 && sign == -1)
			return (0);
		i++;
	}
	return (re * sign);
}
