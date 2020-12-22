/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:56:54 by hroh              #+#    #+#             */
/*   Updated: 2020/12/22 22:38:21 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	ray_loop_cal_step(t_ray *ray)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (ray->posX - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - ray->posX) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (ray->posY - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - ray->posY) * ray->deltaDistY;
	}
}

void	ray_loop_cal_hit(t_env *env, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (!ft_strchr("02NEWS", env->map[ray->mapX][ray->mapY]))
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perpWallDist = (ray->mapX - ray->posX + (1 - ray->stepX) / 2) / ray->rayDirX;
	else
		ray->perpWallDist = (ray->mapY - ray->posY + (1 - ray->stepY) / 2) / ray->rayDirY;
}

void	ray_cal_wall(t_env *env, t_ray *ray)
{
	ray->line_H = (int)(env->height / ray->perpWallDist);
	ray->drawStart = (-ray->line_H + env->height) / 2;
	ray->drawEnd = (ray->line_H + env->height) / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	if (ray->drawEnd >= env->height)
		ray->drawEnd = env->height - 1;
	if (ray->side == 0)
		ray->texNum = (ray->rayDirX > 0) ? 1 : 0;
	else
		ray->texNum = (ray->rayDirY < 0) ? 3 : 2;
	ray->wall_x = (ray->side == 0) ? ray->posY + ray->perpWallDist * ray->rayDirY
	: ray->posX + ray->perpWallDist * ray->rayDirX;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x =
		(int)(ray->wall_x * (double)ray->texture_size[ray->texNum].x);
	
	if (ray->texNum == 1 || ray->texNum == 3)
		ray->tex_x = ray->texture_size[ray->texNum].x - ray->tex_x - 1;
}

void	ray_loop_init(t_env *env, t_ray *ray, int x)
{
	ray->cameraX = 2 * x / (double)env->width - 1;
	ray->rayDirX = ray->dirX + ray->planeX * ray->cameraX;
	ray->rayDirY = ray->dirY + ray->planeY * ray->cameraX;
	ray->mapX = (int)ray->posX;
	ray->mapY = (int)ray->posY;
	ray->deltaDistX = (ray->rayDirY == 0) ? 0 : ((ray->rayDirX == 0) ? 1 : fabs(1 / ray->rayDirX));
	ray->deltaDistY = (ray->rayDirX == 0) ? 0 : ((ray->rayDirY == 0) ? 1 : fabs(1 / ray->rayDirY));
	ray->hit = 0;
	ray_loop_cal_step(ray);
	ray_loop_cal_hit(env, ray);
	draw_map_ray(env, ray, x);
	ray->zbuffer[x] = ray->perpWallDist;
}

void	ray_loop(t_env *env, t_ray	*ray)
{
	int		x;
	double	st;
	int		color;

	x = -1;
	while (++x < env->width)
	{
		ray_loop_init(env, ray, x);
		if (env->map_mode == 0)
		{
			ray_cal_wall(env, ray);
			st = ray->texture_size[ray->texNum].y * 1.0 / ray->line_H;
			ray->tex_pos = (ray->drawStart + (ray->line_H - env->height) / 2) * st;
			while (ray->drawStart < ray->drawEnd)
			{
				ray->tex_y = (int)ray->tex_pos;
				ray->tex_pos += st;
				color = ray->texture[ray->texNum][
					ray->texture_size[ray->texNum].x * ray->tex_y + ray->tex_x];
				if (env->night_mode == 1)
					color = (color >> 1) & 8355711;
				ray->img->data[ray->drawStart * env->width + x] = color;
				ray->drawStart++;
			}
		}
	}
}
