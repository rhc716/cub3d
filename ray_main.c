/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 17:17:38 by hroh              #+#    #+#             */
/*   Updated: 2020/12/18 18:10:51 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int 	ft_close(t_env *env)
{
	free_all(env);
	exit(0);
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
	if (env->ray->map_on == 1)
	{
		draw_background(env, 1);
		draw_map(env);
		draw_lines(env);
		ray_main_loop(env);
	}
	else
	{
		draw_background(env, 2);
		ray_main_loop(env);
	}
	mlx_put_image_to_window(env->ray->mlx, env->ray->win, env->ray->img->img, 0, 0);
	return (0);
}

int	ray_caster(t_env *env, t_err *err, int c)
{
	t_ray *ray;

	if (!(ray = (t_ray *)malloc(sizeof(t_ray))) || !init_ray(ray, env))
		return (add_err_msg(err, "malloc error"));
	if (c == 2)
	{
		write(1, "screen shot!!\n", 14);
		return (0);
	}
	ray_init(ray, env);
	mlx_hook(ray->win, X_EVENT_KEY_PRESS, KeyPressMask, &deal_key, env);
	mlx_loop_hook(ray->mlx, &main_loop, env);
	mlx_loop(ray->mlx);
	return (0);
}
