/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 16:55:23 by hroh              #+#    #+#             */
/*   Updated: 2020/12/18 16:55:47 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(t_env *env, int c)
{
	int i;
	int j;
	int color;
	
	color = 0x000000;
	i = -1;
	if (c == 2)
		color = env->ceiling;
	while (++i < env->height / 2)
	{
		j = -1;
		while (++j < env->width)
			env->ray->img->data[i * env->width + j] = color;
	}
	i = env->height / 2 - 1;
	if (c == 2)
		color = env->floor;
	while (++i < env->height)
	{
		j = -1;
		while (++j < env->width)
			env->ray->img->data[i * env->width + j] = color;
	}
}
