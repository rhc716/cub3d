/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 20:20:39 by hroh              #+#    #+#             */
/*   Updated: 2020/12/21 20:36:55 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_2d_array(void **array, int len)
{
	int i;

	i = 0;
	while (array[i])
	{
		if (len != 0)
		{
			if (i < len)
				free(array[i]);
		}
		else
			free(array[i]);
		i++;
		if (len != 0 && i == len)
		{
			free(array);
			return ;
		}
	}
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
		free_2d_array((void **)env->map, 0);
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
		if (env->ray->texture)
			free_2d_array((void **)(env->ray->texture), 5);
		if (env->ray->texture_size)
			free(env->ray->texture_size);
		if (env->ray->zbuffer)
			free(env->ray->zbuffer);
	}
	free(env->ray);
	free(env);
	return (0);
}
