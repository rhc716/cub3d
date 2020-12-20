/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:56:54 by hroh              #+#    #+#             */
/*   Updated: 2020/12/20 21:18:56 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
}

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


void	draw_vertical(t_env *env, int x, int y1, int y2)
{
	int		i;
	t_ray	*ray;
	int		 color;

	ray = env->ray;
	color = 0xCCCCCC;
	if (env->map[ray->mapX][ray->mapY] == '1')
    	color = 0x000080;
	else if (env->map[ray->mapX][ray->mapY] == '2')
    	color = 0x999900;
    if (ray->side == 1)
		color = color / 2;
	i = y1 - 1;
	while (++i <= y2)
		ray->img->data[i * env->width + x] = color;
}

/*
void	ray_cal_wall(t_ray *ray, int x)
{
	if (ray->side == 0)
	{
		ray->texNum = (ray->rayDirX > 0) ? 1 : 0;
		ray->wall_x = ray->posY + ray->perpWallDist * ray->rayDirY;
	}
	else
	{
		ray->texNum = (ray->rayDirY < 0) ? 3 : 2;
		ray->wall_x = ray->posX + ray->perpWallDist * ray->rayDirX;
	}
}
*/	
void	ray_loop(t_env *env)
{
	int		x;
	t_ray	*ray;

	x = -1;
	ray = env->ray;
	while (++x < env->width)
	{
		ray_loop_init(env, ray, x);
		ray_loop_cal_step(ray);
		ray_loop_cal_hit(env, ray);
		draw_map_ray(env, ray, x);
		ray->lineHeight = (int)(env->height / ray->perpWallDist);
		ray->drawStart = -ray->lineHeight / 2 + env->height / 2;
		if (ray->drawStart < 0)
			ray->drawStart = 0;
		ray->drawEnd = ray->lineHeight / 2 + env->height / 2;
		if (ray->drawEnd >= env->height)
			ray->drawEnd = env->height - 1;
		if (ray->map_on == 0)
			draw_vertical(env, x, ray->drawStart, ray->drawEnd);
	}
}
