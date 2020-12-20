/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 17:17:38 by hroh              #+#    #+#             */
/*   Updated: 2020/12/20 21:43:27 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int 	ft_close(t_env *env)
{
	free_all(env);
	exit(0);
}

void	init_window(t_ray *ray, t_env *env)
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
		draw_player(env, 0xFFCC33);
	}
	else
		draw_background(env, 2);
	ray_loop(env);
	mlx_put_image_to_window(env->ray->mlx, env->ray->win, env->ray->img->img, 0, 0);
	return (0);
}

int			load_image(t_ray *ray, int i, char *path, t_img *img, t_err *err)
{
	int		x;
	int		y;

	//printf("i : %d path %s\n", i, path);
	img->img =
		mlx_xpm_file_to_image(ray->mlx, path, &img->width, &img->height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp,
		&img->size_l, &img->endian);
	ray->texture_size[i].x = img->width;
	ray->texture_size[i].y = img->height;
	if (!(ray->texture[i] =
		(int *)malloc(sizeof(int) * (img->width * img->height))))
		return (add_err_msg(err, "malloc error"));
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			ray->texture[i][img->width * y + x] =
				img->data[img->width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(ray->mlx, img->img);
	return (0);
}

int			load_texture(t_env *env, t_ray *ray, t_err *err)
{
	t_img	buf;

	if (!(ray->texture =
		(int **)malloc(sizeof(int*) * (5))))
		return (add_err_msg(err, "malloc error"));
	if (!(ray->texture_size =
		(s_pos *)malloc(sizeof(s_pos) * (5))))
		return (add_err_msg(err, "malloc error"));
	load_image(ray, 0, env->no, &buf, err);
	load_image(ray, 1, env->so, &buf, err);
	load_image(ray, 2, env->we, &buf, err);
	load_image(ray, 3, env->ea, &buf, err);
	load_image(ray, 4, env->sp, &buf, err);
	return (0);
}

int	ray_caster(t_env *env, t_err *err, int argc)
{
	t_ray *ray;

	if (!(ray = (t_ray *)malloc(sizeof(t_ray))) || !init_ray(ray, env))
		return (add_err_msg(err, "malloc error"));
	if (argc == 2)
	{
		init_window(ray, env);
		if (load_texture(env, ray, err) == -1 || err->env_error > 0)
			return (add_err_msg(err, "texture load error"));
		mlx_hook(ray->win, X_EVENT_KEY_PRESS, KeyPressMask, &deal_key, env);
		mlx_loop_hook(ray->mlx, &main_loop, env);
		mlx_loop(ray->mlx);
	}
	else
		write(1, "screen shot!!\n", 14);
	return (0);
}
