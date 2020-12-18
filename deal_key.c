/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 16:56:53 by hroh              #+#    #+#             */
/*   Updated: 2020/12/18 18:10:07 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	deal_wasd(int key_code, t_env *env, double *oldDirX, double *oldPlaneX)
{
	double sign;
	t_ray *ray;

	ray = env->ray;
	sign = (key_code == KEY_W || key_code == KEY_A) ? 1 : -1;
	if (key_code == KEY_W || key_code == KEY_S)
    {
    	if(ft_strchr("0NEWS", env->map[(int)(ray->posX + sign * ray->dirX * ray->moveSpeed)][(int)ray->posY]))
			ray->posX += sign * ray->dirX * ray->moveSpeed;
    	if(ft_strchr("0NEWS", env->map[(int)ray->posX][(int)(ray->posY + sign * ray->dirY * ray->moveSpeed)]))
			ray->posY += sign * ray->dirY * ray->moveSpeed;
    }
    if (key_code == KEY_D || key_code == KEY_A)
    {
		*oldDirX = ray->dirX;
		ray->dirX = ray->dirX * cos(sign * ray->rotSpeed) - ray->dirY * sin(sign * ray->rotSpeed);
		ray->dirY = *oldDirX * sin(sign *ray->rotSpeed) + ray->dirY * cos(sign *ray->rotSpeed);
		*oldPlaneX = ray->planeX;
		ray->planeX = ray->planeX * cos(sign *ray->rotSpeed) - ray->planeY * sin(sign *ray->rotSpeed);
		ray->planeY = *oldPlaneX * sin(sign *ray->rotSpeed) + ray->planeY * cos(sign *ray->rotSpeed);
    }
}

void	deal_left_right(int key_code, t_env *env, double *oldDirX, double *oldPlaneX)
{
	double sign;
	t_ray *ray;

	ray = env->ray;
	sign = (key_code == KEY_LEFT) ? 1 : -1;
	if (!ray->dirX_bak)
	{
		ray->dirX_bak = ray->dirX;
		ray->dirY_bak = ray->dirY;
		ray->planeX_bak = ray->planeX;
		ray->planeY_bak = ray->planeY;
		ray->befor_key = 0;
	}
	if ((key_code == KEY_RIGHT && ray->befor_key != KEY_RIGHT)
		|| (key_code == KEY_LEFT && ray->befor_key != KEY_LEFT))
	{
		*oldDirX = ray->dirX;
		ray->dirX = ray->dirX * cos(sign * 1.5) - ray->dirY * sin(sign * 1.5);
		ray->dirY = *oldDirX * sin(sign * 1.5) + ray->dirY * cos(sign * 1.5);
		*oldPlaneX = ray->planeX;
		ray->planeX = ray->planeX * cos(sign * 1.5) - ray->planeY * sin(sign * 1.5);
		ray->planeY = *oldPlaneX * sin(sign * 1.5) + ray->planeY * cos(sign * 1.5);
	}
}

int		deal_key(int key_code, t_env *env)
{
	t_ray *ray;
	double oldDirX;
	double oldPlaneX;

	ray = env->ray;
	if (key_code == KEY_ESC)
		ft_close(env);
	if (key_code == KEY_W || key_code == KEY_S || key_code == KEY_D || key_code == KEY_A)
		deal_wasd(key_code, env, &oldDirX, &oldPlaneX);
	if (key_code == KEY_LEFT || key_code == KEY_RIGHT)
		deal_left_right(key_code, env, &oldDirX, &oldPlaneX);
	if (ray->dirX_bak && (ray->befor_key == KEY_LEFT || ray->befor_key == KEY_RIGHT) && ray->befor_key != key_code)
	{
		ray->dirX = ray->dirX_bak;
		ray->dirY = ray->dirY_bak;
		ray->planeX = ray->planeX_bak;
		ray->planeY = ray->planeY_bak;
		ray->dirX_bak = 0;
	}
	if (key_code == KEY_TAB && ray->map_on == 0)
		ray->map_on = 1;
	else if (key_code == KEY_TAB && ray->map_on == 1)
		ray->map_on = 0;
	ray->befor_key = key_code;
	return (0);
}
