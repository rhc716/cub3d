/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:56:54 by hroh              #+#    #+#             */
/*   Updated: 2020/12/19 21:45:10 by hroh             ###   ########.fr       */
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

void	draw_player(t_env *env, int color)
{
	t_ray	*ray;
	double	x;
	double	y;
	int		i;
	int		j;

	ray = env->ray;
	x = ray->posX;
	y = ray->posY;
	i = -4;
	while (++i < 4)
	{
		j = -4;
		while (++j < 4)
			ray->img->data[(int)(floor(x * ray->tilesize_y + i)) * env->width + (int)(y * ray->tilesize_x + j)] = color;
	}
}

void	ray_main_loop(t_env *env)
{
	int		x;
	t_ray	*ray;

	x = -1;
	ray = env->ray;
	if (ray->map_on == 1)
		draw_player(env, 0xFFCC33);
	while (++x < env->width)
	{
		ray->cameraX = 2 * x / (double)env->width - 1;
		ray->rayDirX = ray->dirX + ray->planeX * ray->cameraX;
		ray->rayDirY = ray->dirY + ray->planeY * ray->cameraX;
		ray->mapX = (int)ray->posX;
		ray->mapY = (int)ray->posY;
    	ray->deltaDistX = (ray->rayDirY == 0) ? 0 : ((ray->rayDirX == 0) ? 1 : fabs(1 / ray->rayDirX));
    	ray->deltaDistY = (ray->rayDirX == 0) ? 0 : ((ray->rayDirY == 0) ? 1 : fabs(1 / ray->rayDirY));
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
        	if (!ft_strchr("02NEWS", env->map[ray->mapX][ray->mapY]))
				ray->hit = 1;
    	}
		if (ray->map_on == 1 && x % 20 == 0)
		{
			double x1;
			double y1;
			double dDistX;
			double dDistY;
			
			dDistX = ray->rayDirX / ray->tilesize_y;
			dDistY = ray->rayDirY / ray->tilesize_x;
			x1 = ray->posX;
			y1 = ray->posY;
			while (ft_strchr("02NEWS", env->map[(int)x1][(int)y1]))
			{
				x1 += dDistX;
				y1 += dDistY;
				ray->img->data[(int)(floor(x1 * ray->tilesize_y) * env->width + (int)(y1 * ray->tilesize_x))] = 0x3399FF;
			}
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
