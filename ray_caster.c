/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:56:54 by hroh              #+#    #+#             */
/*   Updated: 2020/12/17 22:59:03 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ver(t_env *env, int x, int y1, int y2, int color)
{
	int		i;
	t_ray	*ray;

	ray = env->ray;
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
        	if (env->map[ray->mapX][ray->mapY] > '0')
				ray->hit = 1;
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
		int color;
		 switch(env->map[ray->mapX][ray->mapY])
      {
        case 1:  color = 0xb3b3b3;  break;
        case 2:  color = 0xA00000;  break;
		case 3:  color = 0x00A000;  break;
		case 4:  color = 0x0000A0;  break;
        default: color = 0x000080; break;
      }
      if (ray->side == 1) {color = color / 2;}
		draw_ver(env, x, drawStart, drawEnd, color);
	}
}
