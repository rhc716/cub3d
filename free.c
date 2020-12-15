/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 20:20:39 by hroh              #+#    #+#             */
/*   Updated: 2020/12/15 18:19:28 by hroh             ###   ########.fr       */
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
	if (env->map)
		free_2d_array(env->map);
	if (env->ray)
	{
		if (env->ray->mlx)
		{
			mlx_destroy_image(env->ray->mlx, env->ray->img->img);
			mlx_destroy_window(env->ray->mlx, env->ray->win);
			mlx_destroy_display(env->ray->mlx);
			free(env->ray->mlx);
		}
		free(env->ray->img);
	}
	free(env->ray);
	free(env);
	return (0);
}
