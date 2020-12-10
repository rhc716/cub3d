/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 18:23:55 by hroh              #+#    #+#             */
/*   Updated: 2020/12/10 20:00:01 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			check_valid_path(char *path)
{
	int	fd;

	if ((fd = open(path, O_RDONLY)) == -1)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

static int	find_hole_in_map(char **map, int i, int j)
{
	if (map[i - 1][j - 1] && map[i - 1][j] && map[i - 1][j + 1] && map[i][j - 1]
		&& map[i][j + 1] && map[i + 1][j - 1] && map[i + 1][j]
		&& map[i + 1][j + 1])
		if (!ft_isspace(map[i - 1][j - 1]) && !ft_isspace(map[i - 1][j])
			&& !ft_isspace(map[i - 1][j + 1]) && !ft_isspace(map[i][j - 1])
			&& !ft_isspace(map[i][j + 1]) && !ft_isspace(map[i + 1][j - 1])
			&& !ft_isspace(map[i + 1][j]) && !ft_isspace(map[i + 1][j + 1]))
			return (1);
	return (-1);
}

static int	check_valid_map(t_env *env)
{
	int i;
	int j;
	int	cnt;

	cnt = 0;
	i = -1;
	while (env->map[++i])
	{
		j = -1;
		while (env->map[i][++j])
		{
			if (ft_strchr("NEWS", env->map[i][j]))
				cnt++;
			if (ft_strchr("012 NEWS", env->map[i][j]) == 0)
				return (add_err_msg(env, "\nMap error, illegal characters"));
			if (env->map[i][j] == '0' && find_hole_in_map(env->map, i, j) == -1)
				return (add_err_msg(env, "\nMap error, 0 next blank or NULL"));
		}
	}
	if (cnt != 1)
		return (add_err_msg(env, "\nMap error, Problems with player location"));
	return (0);
}

int			check_valid_env(t_env *env) // mlx)
{
	// 추가 필요
	// int sizex;
	// int sizey;
	//mlx_get_screen_size(mlx, &sizex, &sizey);
	if (env->width <= 0 || env->height <= 0) // || env->width > sizex || env->height > sizey)
		add_err_msg(env, "\nThe resolution value is not valid");
	if (!env->no || !env->so || !env->we || !env->ea || !env->sp)
		add_err_msg(env, "\nThere is at least 1 incomplete image path");
	check_valid_map(env);
	if (env->env_error > 0)
		return (-1);
	return (0);
}
