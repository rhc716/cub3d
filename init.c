/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 18:35:22 by hroh              #+#    #+#             */
/*   Updated: 2020/12/14 18:35:38 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		init_env(t_env *env)
{
	env->width = 0;
	env->height = 0;
	env->no = NULL;
	env->so = NULL;
	env->we = NULL;
	env->ea = NULL;
	env->sp = NULL;
	env->map = NULL;
	env->floor = 0;
	env->ceiling = 0;
	env->row = 0;
	env->col = 0;
	env->posX_init = 0;
	env->posY_init = 0;
	env->dirX_init = 0;
	env->dirY_init = 0;
	env->env_error = 0;
	env->env_error_msg = NULL;
}