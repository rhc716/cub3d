/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 17:17:38 by hroh              #+#    #+#             */
/*   Updated: 2020/12/15 18:00:33 by hroh             ###   ########.fr       */
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
	int i;
	i = 0;
	while (env->ray->img->data[i])
		i++;
	while (fabs(x2 - x1) > 0.01 || fabs(y2 - y1) > 0.01)
	{
		env->ray->img->data[to_coord(x1, y1, env)] = 0xb3b3b3;
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
/*
void	draw_block(t_env *env, int x, int y, int color)
{
	int		i;
	int		j;
	t_ray	*ray;

	ray = env->ray;
	x *= ray->tilesize;
	y *= ray->tilesize;
	i = 0;
	while (i < ray->tilesize)
	{
		j = 0;
		while (j < ray->tilesize)
		{
			env->ray->img->data[(y + i) * env->width + x + j] = color;
			j++;
		}
		i++;
	}
}

void	draw_map(t_env *env)
{
	int		i;
	int		j;
	int 	color;
	t_ray	*ray;

	ray = env->ray;
	color = 0xA080A0;
	i = 0;
	while (i < env->row)
	{
		j = 0;
		while (j < env->col)
		{
			if (env->map[i][j] == 1)
				draw_block(env, j, i, color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(ray->mlx, ray->win, ray->img->img, 0, 0);
}
*/
int 	ft_close(t_env *env)
{
	free_all(env);
	exit(0);
}

int		deal_key(int key_code, t_env *env)
{
	if (key_code == KEY_ESC)
		ft_close(env);
	return (0);
}

void	ray_init(t_ray *ray, t_env *env)
{
	ray->mlx = mlx_init();
	ray->win = mlx_new_window(ray->mlx, env->width, env->height, "cub3d");
	ray->img->img = mlx_new_image(ray->mlx, env->width, env->height);
	ray->img->data = (int *)mlx_get_data_addr(ray->img->img, &ray->img->bpp, &ray->img->size_l, &ray->img->endian);
}

int		main_loop(t_env *env)
{
	//draw_map(env);
	mlx_put_image_to_window(env->ray->mlx, env->ray->win, env->ray->img->img, 0, 0);
	return (0);
}

int	ray_caster(t_env *env, t_err *err, int c)
{
	t_ray *ray;

	if(!(ray = (t_ray *)malloc(sizeof(t_ray))) || !init_ray(ray, env))
		return (add_err_msg(err, "malloc error"));
	if (c == 2)
	{
		write(1, "screen shot!!\n", 14);
		return (0);
	}
	ray_init(ray, env);
	mlx_hook(ray->win, X_EVENT_KEY_PRESS, KeyPressMask, &deal_key, env);
	mlx_hook(ray->win, X_EVENT_KEY_EXIT, 0, &ft_close, env);
	draw_lines(env);
	mlx_loop_hook(ray->mlx, &main_loop, env);
	mlx_loop(ray->mlx);
	return (0);
}
