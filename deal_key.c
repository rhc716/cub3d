/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 16:56:53 by hroh              #+#    #+#             */
/*   Updated: 2020/12/24 21:47:40 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	deal_wasd(int key_code, t_env *env)
{
	double	sign;
	t_ray	*ray;

	ray = env->ray;
	sign = (key_code == KEY_W) ? 1 : -1;
	if (key_code == KEY_W || key_code == KEY_S)
	{
		if (ft_strchr("02NEWS", env->map[(int)(ray->posx + sign *
			2 * ray->dirx * ray->movespeed)][(int)ray->posy]))
			ray->posx += sign * ray->dirx * ray->movespeed;
		if (ft_strchr("02NEWS", env->map[(int)ray->posx][(int)(ray->posy +
			sign * 2 * ray->diry * ray->movespeed)]))
			ray->posy += sign * ray->diry * ray->movespeed;
	}
	if (key_code == KEY_D || key_code == KEY_A)
	{
		sign = (key_code == KEY_A) ? -1 : 1;
		if (ft_strchr("02NEWS", env->map[(int)(ray->posx + sign * ray->diry *
			2 * ray->movespeed)][(int)ray->posy]))
			ray->posx += sign * ray->diry * ray->movespeed;
		sign = (key_code == KEY_D) ? -1 : 1;
		if (ft_strchr("02NEWS", env->map[(int)ray->posx][(int)(ray->posy +
			sign * ray->dirx * 2 * ray->movespeed)]))
			ray->posy += sign * ray->dirx * ray->movespeed;
	}
}

void	deal_left_right(int key_code, t_ray *ray)
{
	double sign;
	double olddirx;
	double oldplanex;

	olddirx = ray->dirx;
	oldplanex = ray->planex;
	sign = (key_code == KEY_LEFT) ? 1 : -1;
	ray->dirx = ray->dirx * cos(sign * ray->rotspeed) -
	ray->diry * sin(sign * ray->rotspeed);
	ray->diry = olddirx * sin(sign * ray->rotspeed) +
	ray->diry * cos(sign * ray->rotspeed);
	ray->planex = ray->planex * cos(sign * ray->rotspeed) -
	ray->planey * sin(sign * ray->rotspeed);
	ray->planey = oldplanex * sin(sign * ray->rotspeed) +
	ray->planey * cos(sign * ray->rotspeed);
}

int		deal_key(int key_code, t_env *env)
{
	t_ray *ray;

	ray = env->ray;
	if (key_code == KEY_ESC)
		ft_close(env);
	if (key_code == KEY_W || key_code == KEY_S ||
		key_code == KEY_D || key_code == KEY_A)
		deal_wasd(key_code, env);
	if (key_code == KEY_LEFT || key_code == KEY_RIGHT)
		deal_left_right(key_code, ray);
	if (key_code == KEY_TAB)
		env->map_mode = (env->map_mode == 1) ? 0 : 1;
	if (key_code == KEY_1)
		env->night_mode = (env->night_mode == 1) ? 0 : 1;
	return (0);
}
