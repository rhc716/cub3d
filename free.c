/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 20:20:39 by hroh              #+#    #+#             */
/*   Updated: 2020/12/24 20:15:18 by hroh             ###   ########.fr       */
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

void	free_ray(t_env *env)
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
		free_2d_array((void **)(env->ray->texture), env->tex_cnt);
	if (env->ray->texture_size)
		free(env->ray->texture_size);
	if (env->ray->zbuffer)
		free(env->ray->zbuffer);
	if (env->ray->sprite)
		free(env->ray->sprite);
	if (env->ray->sp_env)
		free(env->ray->sp_env);
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
		free_ray(env);
	free(env->ray);
	free(env);
	return (0);
}
