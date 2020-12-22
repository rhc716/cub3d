/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 17:20:51 by hroh              #+#    #+#             */
/*   Updated: 2020/12/22 22:36:29 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			load_image(t_ray *ray, int i, char *path, t_img *img, t_err *err)
{
	int		x;
	int		y;

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
		(int **)malloc(sizeof(int*) * (env->tex_cnt))))
		return (add_err_msg(err, "malloc error"));
	if (!(ray->texture_size =
		(s_pos *)malloc(sizeof(s_pos) * (env->tex_cnt))))
		return (add_err_msg(err, "malloc error"));
	load_image(ray, 0, env->no, &buf, err);
	load_image(ray, 1, env->so, &buf, err);
	load_image(ray, 2, env->we, &buf, err);
	load_image(ray, 3, env->ea, &buf, err);
	load_image(ray, 4, env->sp, &buf, err);
	load_image(ray, 5, "./texture/ceiling.xpm", &buf, err);
	return (0);
}
