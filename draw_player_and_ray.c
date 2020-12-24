/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_and_ray.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 19:30:42 by hroh              #+#    #+#             */
/*   Updated: 2020/12/24 21:47:46 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_env *env, int color)
{
	t_ray	*ray;
	double	x;
	double	y;
	int		i;
	int		j;

	ray = env->ray;
	x = ray->posx;
	y = ray->posy;
	i = -4;
	while (++i < 4)
	{
		j = -4;
		while (++j < 4)
			ray->img->data[(int)(floor(x * ray->tilesize_y + i)) * env->width
			+ (int)(y * ray->tilesize_x + j)] = color;
	}
}

void	draw_map_ray(t_env *env, t_ray *ray, int x)
{
	double	x1;
	double	y1;
	double	distx;
	double	disty;
	int		color;

	if (env->map_mode == 1 && x % 10 == 0)
	{
		distx = ray->raydirx / ray->tilesize_y;
		disty = ray->raydiry / ray->tilesize_x;
		x1 = ray->posx;
		y1 = ray->posy;
		while (ft_strchr("02NEWS", env->map[(int)x1][(int)y1]))
		{
			color = (ft_strchr("2", env->map[(int)x1]
			[(int)y1])) ? 0xFFCC33 : 0x6699CC;
			ray->img->data[(int)(floor(x1 * ray->tilesize_y) * env->width
			+ (int)(y1 * ray->tilesize_x))] = color;
			x1 += distx;
			y1 += disty;
		}
	}
}
