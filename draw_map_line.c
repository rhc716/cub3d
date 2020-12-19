/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 16:50:37 by hroh              #+#    #+#             */
/*   Updated: 2020/12/19 21:42:01 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		to_coord(double x, double y, t_env *env)
{
	return ((int)floor(y) * env->width + (int)floor(x));
}

void	draw_line(t_env *env, double x1, double y1, double x2, double y2)
{
	double	deltaX;
	double	deltaY;
	double	step;

	deltaX = x2 - x1;
	deltaY = y2 - y1;
	step = (fabs(deltaX) > fabs(deltaY)) ? fabs(deltaX) : fabs(deltaY);
	deltaX /= step;
	deltaY /= step;
	while (fabs(x2 - x1) > 0.01 || fabs(y2 - y1) > 0.01)
	{
		env->ray->img->data[to_coord(x1, y1, env)] = 0x663300;
		x1 += deltaX;
		y1 += deltaY;
	}
}

void 	draw_lines(t_env *env)
{
	int		i;
	int		j;
	double	ts_x;
	double	ts_y;

	i = 0;
	ts_x = env->ray->tilesize_x;
	ts_y = env->ray->tilesize_y;
	while (i * ts_x < env->width)
	{
		draw_line(env, i * ts_x, 0, i * ts_x, env->height);
		i++;
	}
	draw_line(env, env->col * ts_x - 1, 0, env->col * ts_x - 1, env->height);
	j = 0;
	while (j * ts_y < env->height)
	{
		draw_line(env, 0, j * ts_y, env->width, j * ts_y);
		j++;
	}
	draw_line(env, 0, env->row * ts_y - 1, env->width, env->row * ts_y - 1);
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
				draw_block(env, j, i, 0x33CC99);
			j++;
		}
		i++;
	}
}
