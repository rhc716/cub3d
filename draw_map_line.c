/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 16:50:37 by hroh              #+#    #+#             */
/*   Updated: 2020/12/24 20:39:46 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		to_coord(double x, double y, t_env *env)
{
	return ((int)floor(y) * env->width + (int)floor(x));
}

void	draw_line(t_env *env, double x1, double y1)
{
	double	deltax;
	double	deltay;
	double	step;
	double	x2;
	double	y2;

	x2 = env->x2;
	y2 = env->y2;
	deltax = x2 - x1;
	deltay = y2 - y1;
	step = (fabs(deltax) > fabs(deltay)) ? fabs(deltax) : fabs(deltay);
	deltax /= step;
	deltay /= step;
	while (fabs(x2 - x1) > 0.01 || fabs(y2 - y1) > 0.01)
	{
		env->ray->img->data[to_coord(x1, y1, env)] = 0x663300;
		x1 += deltax;
		y1 += deltay;
	}
}

void	draw_lines(t_env *env, double tx, double ty)
{
	int		i;

	i = -1;
	while (++i * tx < env->width)
	{
		env->x2 = i * tx;
		env->y2 = env->height;
		draw_line(env, i * tx, 0);
	}
	env->x2 = env->col * tx - 1;
	env->y2 = env->height;
	draw_line(env, env->col * tx - 1, 0);
	i = -1;
	while (++i * ty < env->height)
	{
		env->x2 = env->width;
		env->y2 = i * ty;
		draw_line(env, 0, i * ty);
	}
	env->x2 = env->width;
	env->y2 = env->row * ty - 1;
	draw_line(env, 0, env->row * ty - 1);
}

void	draw_block(t_env *env, int x, int y, int color)
{
	int		i;
	int		j;
	t_ray	*ray;

	ray = env->ray;
	x *= ray->tilesize_x;
	y *= ray->tilesize_y;
	i = 0;
	while (i < ray->tilesize_y)
	{
		j = 0;
		while (j < ray->tilesize_x)
		{
			env->ray->img->data[(y + i) * (int)(env->width) + x + j] = color;
			j++;
		}
		i++;
	}
}

void	draw_map(t_env *env)
{
	int		i;
	int		j;

	i = 0;
	while (env->map[i])
	{
		j = 0;
		while (env->map[i][j])
		{
			if (env->map[i][j] == '1')
				draw_block(env, j, i, 0x999999);
			if (env->map[i][j] == '2')
				draw_block(env, j, i, 0x660033);
			j++;
		}
		i++;
	}
}
