/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:56:54 by hroh              #+#    #+#             */
/*   Updated: 2020/12/24 21:47:26 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_loop_cal_step(t_ray *ray)
{
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (ray->posx - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1.0 - ray->posx) * ray->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (ray->posy - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1.0 - ray->posy) * ray->deltadisty;
	}
}

void	ray_loop_cal_hit(t_env *env, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (!ft_strchr("02NEWS", env->map[ray->mapx][ray->mapy]))
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perpwalldist = (ray->mapx - ray->posx +
		(1 - ray->stepx) / 2) / ray->raydirx;
	else
		ray->perpwalldist = (ray->mapy - ray->posy +
		(1 - ray->stepy) / 2) / ray->raydiry;
}

void	ray_cal_wall(t_env *env, t_ray *ray)
{
	ray->line_h = (int)(env->height / ray->perpwalldist);
	ray->drawstart = (-ray->line_h + env->height) / 2;
	ray->drawend = (ray->line_h + env->height) / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	if (ray->drawend >= env->height)
		ray->drawend = env->height - 1;
	if (ray->side == 0)
		ray->texnum = (ray->raydirx > 0) ? 1 : 0;
	else
		ray->texnum = (ray->raydiry < 0) ? 3 : 2;
	ray->wall_x = (ray->side == 0) ? ray->posy + ray->perpwalldist *
	ray->raydiry : ray->posx + ray->perpwalldist * ray->raydirx;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x =
		(int)(ray->wall_x * (double)ray->texture_size[ray->texnum].x);
	if (ray->texnum == 1 || ray->texnum == 3)
		ray->tex_x = ray->texture_size[ray->texnum].x - ray->tex_x - 1;
}

void	ray_loop_init(t_env *env, t_ray *ray, int x)
{
	ray->camerax = 2 * x / (double)env->width - 1;
	ray->raydirx = ray->dirx + ray->planex * ray->camerax;
	ray->raydiry = ray->diry + ray->planey * ray->camerax;
	ray->mapx = (int)ray->posx;
	ray->mapy = (int)ray->posy;
	if (ray->raydiry == 0)
	{
		ray->deltadistx = 0;
		ray->deltadisty = 1;
	}
	else if (ray->raydirx == 0)
	{
		ray->deltadistx = 1;
		ray->deltadisty = 0;
	}
	else
	{
		ray->deltadistx = fabs(1 / ray->raydirx);
		ray->deltadisty = fabs(1 / ray->raydiry);
	}
	ray->hit = 0;
	ray_loop_cal_step(ray);
	ray_loop_cal_hit(env, ray);
	draw_map_ray(env, ray, x);
	ray->zbuffer[x] = ray->perpwalldist;
}

void	ray_loop(t_env *env, t_ray *ray)
{
	int		x;
	double	st;
	int		color;

	x = -1;
	while (++x < env->width)
	{
		ray_loop_init(env, ray, x);
		ray_cal_wall(env, ray);
		st = ray->texture_size[ray->texnum].y * 1.0 / ray->line_h;
		ray->tex_pos = (ray->drawstart + (ray->line_h - env->height) / 2) * st;
		while (ray->drawstart < ray->drawend && env->map_mode != 1)
		{
			ray->tex_y = (int)ray->tex_pos;
			ray->tex_pos += st;
			color = ray->texture[ray->texnum][
				ray->texture_size[ray->texnum].x * ray->tex_y + ray->tex_x];
			color = (env->night_mode == 1) ? (color / 2) & 0x7F7F7F : color;
			ray->img->data[ray->drawstart * env->width + x] = color;
			ray->drawstart++;
		}
	}
}
