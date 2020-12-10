/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 20:20:55 by hroh              #+#    #+#             */
/*   Updated: 2020/12/10 20:21:18 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		add_err_msg(t_env *env, char *str)
{
	env->env_error_msg = ft_strjoin(env->env_error_msg, str, 1);
	env->env_error++;
	return (-1);
}

int		print_error(t_env *env, char *str)
{
	write(1, "Error\n", 6);
	if (ft_strlen(str) > 0)
	{
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
	}
	if (errno != 0)
	{
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		write(1, "\n", 1);
	}
	if (env->env_error > 0)
	{
		write(1, &env->env_error_msg[1], ft_strlen(env->env_error_msg));
		write(1, "\n", 1);
	}
	return (0);
}
