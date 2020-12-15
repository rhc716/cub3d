/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 18:35:22 by hroh              #+#    #+#             */
/*   Updated: 2020/12/15 17:29:21 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			init_env(t_env **env)
{
	if (!(*env = (t_env *)malloc(sizeof(t_env))))
		return (0);
	(*env)->width = 0;
	(*env)->height = 0;
	(*env)->no = NULL;
	(*env)->so = NULL;
	(*env)->we = NULL;
	(*env)->ea = NULL;
	(*env)->sp = NULL;
	(*env)->map = NULL;
	(*env)->floor = 0;
	(*env)->ceiling = 0;
	(*env)->row = 0;
	(*env)->col = 0;
	(*env)->posX_init = 0;
	(*env)->posY_init = 0;
	(*env)->dirX_init = 0;
	(*env)->dirY_init = 0;
	(*env)->ray = NULL;
	return (1);
}

int			init_ray(t_ray *ray, t_env *env)
{
	env->ray = ray;
	ray->posX = env->posX_init;
	ray->posY = env->posY_init;
	ray->dirX = env->dirX_init;
	ray->dirY = env->dirY_init;
	ray->planeX = 0;
	ray->planeY = 0.66;
	ray->time = 0;
	ray->oldtime = 0;
	env->width *= 0.9;
	env->height *= 0.9;
	ray->tilesize_x = (double)env->width/(double)env->col;
	ray->tilesize_y = (double)env->height/(double)env->row;
	ray->mlx = NULL;
	ray->win = NULL;
	if (!(ray->img = (t_img *)malloc(sizeof(t_img))))
		return (0);
	return (1);
}

void		init_error(t_err *err)
{
	err->env_error = 0;
	err->env_error_msg = NULL;
}