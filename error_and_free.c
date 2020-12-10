/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 15:42:00 by hroh              #+#    #+#             */
/*   Updated: 2020/12/10 19:00:30 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		add_err_msg(t_env *env, char *str)
{
	env->env_error_msg = ft_strjoin(env->env_error_msg, str, 1);
	env->env_error++;
	return (-1);
}

void	free_2d_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

int		free_all(t_env *env)
{
	free(env->no);
	free(env->so);
	free(env->we);
	free(env->ea);
	free(env->sp);
	free_2d_array(env->map);
	free(env->env_error_msg);
	free(env);
	return (0);
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
