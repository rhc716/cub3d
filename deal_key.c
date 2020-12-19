/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 16:56:53 by hroh              #+#    #+#             */
/*   Updated: 2020/12/19 18:05:58 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	deal_wasd(int key_code, t_env *env)
{
	double sign;
	t_ray *ray;

	ray = env->ray;
	sign = (key_code == KEY_W || key_code == KEY_A) ? 1 : -1;
	if (key_code == KEY_W || key_code == KEY_S)
    {
    	if (ft_strchr("02NEWS", env->map[(int)(ray->posX + sign * 2 * ray->dirX * ray->moveSpeed)][(int)ray->posY]))
			ray->posX += sign * ray->dirX * ray->moveSpeed;
    	if (ft_strchr("02NEWS", env->map[(int)ray->posX][(int)(ray->posY + sign * 2 * ray->dirY * ray->moveSpeed)]))
			ray->posY += sign * ray->dirY * ray->moveSpeed;
    }
	if (key_code == KEY_D || key_code == KEY_A)
    {
		if (ft_strchr("02NEWS", env->map[(int)(ray->posX + sign * ray->dirY * 2 * ray->moveSpeed)][(int)ray->posY]))
			ray->posX += sign * ray->dirY * ray->moveSpeed;
    	if (ft_strchr("02NEWS", env->map[(int)ray->posX][(int)(ray->posY + sign * ray->dirX * 2 * ray->moveSpeed)]))
			ray->posY += sign * ray->dirX * ray->moveSpeed;
    }
}

void	deal_left_right(int key_code, t_ray *ray)
{
	double sign;
	double oldDirX;
	double oldPlaneX;

	oldDirX = ray->dirX;
	oldPlaneX = ray->planeX;
	sign = (key_code == KEY_LEFT) ? 1 : -1;
	ray->dirX = ray->dirX * cos(sign * ray->rotSpeed) - ray->dirY * sin(sign * ray->rotSpeed);
	ray->dirY = oldDirX * sin(sign * ray->rotSpeed) + ray->dirY * cos(sign * ray->rotSpeed);
	ray->planeX = ray->planeX * cos(sign * ray->rotSpeed) - ray->planeY * sin(sign * ray->rotSpeed);
	ray->planeY = oldPlaneX * sin(sign * ray->rotSpeed) + ray->planeY * cos(sign * ray->rotSpeed);
}

int		deal_key(int key_code, t_env *env)
{
	t_ray *ray;

	ray = env->ray;
	if (key_code == KEY_ESC)
		ft_close(env);
	if (key_code == KEY_W || key_code == KEY_S || key_code == KEY_D || key_code == KEY_A)
		deal_wasd(key_code, env);
	if (key_code == KEY_LEFT || key_code == KEY_RIGHT)
		deal_left_right(key_code, ray);
	if (key_code == KEY_TAB && ray->map_on == 0)
		ray->map_on = 1;
	else if (key_code == KEY_TAB && ray->map_on == 1)
		ray->map_on = 0;
	return (0);
}
