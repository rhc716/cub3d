/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:56:54 by hroh              #+#    #+#             */
/*   Updated: 2020/12/18 18:11:56 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	ray_main_loop(t_env *env)
{
	int		x;
	t_ray	*ray;

	x = -1;
	ray = env->ray;
	while (++x < env->width)
	{
		ray->cameraX = 2 * x / (double)env->width - 1;
		ray->rayDirX = ray->dirX + ray->planeX * ray->cameraX;
		ray->rayDirY = ray->dirY + ray->planeY * ray->cameraX;
		ray->mapX = (int)ray->posX;
		ray->mapY = (int)ray->posY;
		ray->deltaDistX = fabs(1 / ray->rayDirX);
		ray->deltaDistY = fabs(1 / ray->rayDirY);
		ray->hit = 0;
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
        	if (!ft_strchr("0NEWS", env->map[ray->mapX][ray->mapY]))
				ray->hit = 1;
    	}
		if (ray->map_on == 1)
		{
			double	deltaX;
			double	deltaY;
			double	step;
			double x1 = ray->posX;
			double y1 = ray->posY;
			double x2 = ray->sideDistX + ray->posX;
			double y2 = ray->sideDistY + ray->posY;
			deltaX = ray->sideDistX;
			deltaY = ray->sideDistY;
			step = (fabs(deltaX) > fabs(deltaY)) ? fabs(deltaX) : fabs(deltaY);
			deltaX /= step;
			deltaY /= step;
			if (!env)
				printf("x1 : %f, y1 : %f, x2 : %f, y2 : %f \n ", x1, y1, x2, y2);
			/*
			while (fabs(x2 - x1) > 0.01 || fabs(y2 - y1) > 0.01)
			{
				printf("x1 : %f, y1 : %f, x2 : %f, y2 : %f \n ", x1, y1, x2, y2);
				env->ray->img->data[(int)floor(y1) * env->width + (int)floor(x1)] = 0x00b3b3;
				x1 += deltaX;
				y1 += deltaY;
			}
			*/
		}
    	if (ray->side == 0)
			ray->perpWallDist = (ray->mapX - ray->posX + (1 - ray->stepX) / 2) / ray->rayDirX;
    	else
			ray->perpWallDist = (ray->mapY - ray->posY + (1 - ray->stepY) / 2) / ray->rayDirY;
	    int lineHeight = (int)(env->height / ray->perpWallDist);
	    int drawStart = -lineHeight / 2 + env->height / 2;
    	if (drawStart < 0)
			drawStart = 0;
    	int drawEnd = lineHeight / 2 + env->height / 2;
		if (drawEnd >= env->height)
			drawEnd = env->height - 1;
		if (ray->map_on == 0)
			draw_vertical(env, x, drawStart, drawEnd);
	}
}
