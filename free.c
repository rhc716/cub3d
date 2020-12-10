/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 20:20:39 by hroh              #+#    #+#             */
/*   Updated: 2020/12/10 20:21:25 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
