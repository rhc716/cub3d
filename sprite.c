/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 19:56:11 by hroh              #+#    #+#             */
/*   Updated: 2020/12/24 21:47:08 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	save_sprite_xy(t_env *env)
{
	int		i;
	int		j;
	int		sp_num;

	sp_num = 0;
	i = -1;
	while (++i < env->row)
	{
		j = -1;
		while (env->map[i][++j])
		{
			if (env->map[i][j] == '2')
			{
				env->ray->sprite[sp_num].x = i;
				env->ray->sprite[sp_num].y = j;
				sp_num++;
			}
		}
	}
}

void	sorting_sprites(t_env *env, t_ray *ray)
{
	int				i;
	int				j;
	t_sprite		temp;

	i = 0;
	while (i < env->sprite_cnt - 1)
	{
		j = i + 1;
		while (j < env->sprite_cnt)
		{
			if (ray->sprite[j].dist > ray->sprite[i].dist)
			{
				temp = ray->sprite[i];
				ray->sprite[i] = ray->sprite[j];
				ray->sprite[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	set_sprite_env(t_env *env, t_ray *ray, t_sp_env *s_env, int i)
{
	s_env->vdiv = 2;
	s_env->vmove = 64.0;
	s_env->sprite_x = ray->sprite[i].x - ray->posx;
	s_env->sprite_y = ray->sprite[i].y - ray->posy;
	s_env->invdet = 1.0 / ((ray->planex * ray->diry)
	- (ray->dirx * ray->planey));
	s_env->trs_x = s_env->invdet * ((ray->diry * s_env->sprite_x)
		- (ray->dirx * s_env->sprite_y));
	s_env->trs_y = s_env->invdet * ((-ray->planey * s_env->sprite_x)
		+ (ray->planex * s_env->sprite_y));
	s_env->sprite_screen_x = (int)((env->width / 2)
		* (1 + s_env->trs_x / s_env->trs_y));
	s_env->sprite_h = (int)fabs(env->height / (s_env->trs_y)) / s_env->vdiv;
	s_env->sprite_w = (int)fabs(env->height / (s_env->trs_y)) / s_env->vdiv;
	s_env->draw_start_y = -s_env->sprite_h / 2 + env->height / 2 + s_env->vmove;
	s_env->draw_start_y = (s_env->draw_start_y < 0) ? 0 : s_env->draw_start_y;
	s_env->draw_end_y = s_env->sprite_h / 2 + env->height / 2 + s_env->vmove;
	if (s_env->draw_end_y >= env->height)
		s_env->draw_end_y = env->height - 1;
	s_env->draw_start_x = -s_env->sprite_w / 2 + s_env->sprite_screen_x;
	s_env->draw_start_x = (s_env->draw_start_x < 0) ? 0 : s_env->draw_start_x;
	s_env->draw_end_x = s_env->sprite_w / 2 + s_env->sprite_screen_x;
	if (s_env->draw_end_x >= env->width)
		s_env->draw_end_x = env->width - 1;
}

void	draw_sprite_texture(t_env *env, t_ray *ray, t_sp_env *s_env, int stripe)
{
	int				tex_x;
	int				tex_y;
	int				y;
	int				d;
	int				color;

	tex_x = (int)(256 *
			(stripe - (-s_env->sprite_w / 2 + s_env->sprite_screen_x))
			* ray->texture_size[4].x / s_env->sprite_w) / 256;
	if (s_env->trs_y > 0 && stripe > 0 && stripe < env->width
		&& s_env->trs_y < ray->zbuffer[stripe])
	{
		y = s_env->draw_start_y;
		while (y < s_env->draw_end_y)
		{
			d = (y - s_env->vmove) * 256 - env->height * 128
			+ s_env->sprite_h * 128;
			tex_y = ((d * ray->texture_size[4].y) / s_env->sprite_h) / 256;
			color = ray->texture[4][ray->texture_size[4].x * tex_y + tex_x];
			color = (env->night_mode == 1) ? (color >> 1) & 8355711 : color;
			if ((color & 0x00FFFFFF) != 0)
				ray->img->data[y * env->width + stripe] = color;
			y++;
		}
	}
}

void	draw_sprite(t_env *env, t_ray *ray)
{
	int i;
	int	stripe;

	i = -1;
	if (env->map_mode == 1)
		return ;
	while (++i < env->sprite_cnt)
	{
		ray->sprite[i].dist =
			((ray->posx - ray->sprite[i].x) * (ray->posx - ray->sprite[i].x)
			+ (ray->posy - ray->sprite[i].y) * (ray->posy - ray->sprite[i].y));
	}
	sorting_sprites(env, ray);
	i = -1;
	while (++i < env->sprite_cnt)
	{
		set_sprite_env(env, ray, ray->sp_env, i);
		stripe = ray->sp_env->draw_start_x;
		while (stripe < ray->sp_env->draw_end_x)
		{
			draw_sprite_texture(env, ray, ray->sp_env, stripe);
			stripe++;
		}
	}
}
