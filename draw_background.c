/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 16:55:23 by hroh              #+#    #+#             */
/*   Updated: 2020/12/24 19:31:12 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_night_ceiling(t_env *env, t_ray *ray)
{
	int		color;
	double	st_y;
	double	st_x;
	int		x;
	int		y;

	ray = env->ray;
	st_x = ray->texture_size[5].x * 1.0 / env->width;
	st_y = ray->texture_size[5].y * 1.0 / (env->height / 2);
	ray->tex_pos_x = 0;
	x = -1;
	while (++x < env->width)
	{
		y = -1;
		ray->tex_pos = 0;
		while (++y < env->height / 2)
		{
			color = ray->texture[5][
			ray->texture_size[5].x * (int)ray->tex_pos + (int)ray->tex_pos_x];
			ray->img->data[y * env->width + x] = color;
			ray->tex_pos += st_y;
		}
		ray->tex_pos_x += st_x;
	}
}

void	draw_ceiling(t_env *env, int c, int color)
{
	int		i;
	int		j;
	t_ray	*ray;

	ray = env->ray;
	if (env->night_mode == 1 && env->map_mode == 0)
		draw_night_ceiling(env, ray);
	else
	{
		i = -1;
		if (c == 2)
			color = env->ceiling;
		while (++i < env->height / 2)
		{
			j = -1;
			while (++j < env->width)
				env->ray->img->data[i * env->width + j] = color;
		}
	}
}

void	draw_background(t_env *env, int c)
{
	int i;
	int j;
	int color;

	color = 0x000000;
	draw_ceiling(env, c, color);
	i = env->height / 2 - 1;
	if (c == 2)
		color = env->floor;
	if (env->night_mode == 1 && env->map_mode == 0)
		color = env->floor / 2;
	while (++i < env->height)
	{
		j = -1;
		while (++j < env->width)
			env->ray->img->data[i * env->width + j] = color;
	}
}
