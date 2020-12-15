/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 20:20:55 by hroh              #+#    #+#             */
/*   Updated: 2020/12/15 13:24:12 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		add_err_msg(t_err *err, char *str)
{
	err->env_error_msg = ft_strjoin(err->env_error_msg, str, 1);
	err->env_error++;
	return (-1);
}

int		print_error_exit(t_err *err, t_env *env, char *str)
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
	if (err->env_error > 0)
	{
		write(1, &err->env_error_msg[1], ft_strlen(err->env_error_msg));
		write(1, "\n", 1);
	}
	if (err->env_error_msg)
		free (err->env_error_msg);
	if (env)
		free_all(env);
	return (0);
}
