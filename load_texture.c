/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 17:20:51 by hroh              #+#    #+#             */
/*   Updated: 2020/12/24 20:20:06 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		load_image(t_ray *ray, int i, char *path, t_img *img)
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
		return (-1);
	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
		{
			ray->texture[i][img->width * y + x] =
				img->data[img->width * y + x];
		}
	}
	mlx_destroy_image(ray->mlx, img->img);
	return (0);
}

int		load_texture(t_env *env, t_ray *ray, t_err *err)
{
	t_img	buf;

	if (!(ray->texture =
		(int **)malloc(sizeof(int*) * (env->tex_cnt))))
		return (add_err_msg(err, "malloc error"));
	if (!(ray->texture_size =
		(t_pos *)malloc(sizeof(t_pos) * (env->tex_cnt))))
		return (add_err_msg(err, "malloc error"));
	if (load_image(ray, 0, env->no, &buf) == -1 ||
		load_image(ray, 1, env->so, &buf) == -1 ||
		load_image(ray, 2, env->we, &buf) == -1 ||
		load_image(ray, 3, env->ea, &buf) == -1 ||
		load_image(ray, 4, env->sp, &buf) == -1 ||
		load_image(ray, 5, "./texture/ceiling.xpm", &buf) == -1)
		return (add_err_msg(err, "malloc error"));
	return (0);
}
