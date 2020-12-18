/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 18:23:55 by hroh              #+#    #+#             */
/*   Updated: 2020/12/18 13:39:42 by hroh             ###   ########.fr       */
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

static void set_player_pos_dir(t_env *env, int *cnt, int i, int j)
{
	(*cnt)++;
	env->posX_init = i;
	env->posY_init = j;
	if (env->map[i][j] == 'N')
	{
		env->dirX_init = -1;
		env->dirY_init = 0;
	}
	if (env->map[i][j] == 'W')
	{
		env->dirX_init = 0;
		env->dirY_init = -1;
	}
	if (env->map[i][j] == 'E')
	{
		env->dirX_init = 0;
		env->dirY_init = 1;
	}
	if (env->map[i][j] == 'S')
	{
		env->dirX_init = 1;
		env->dirY_init = 0;
	}
}

static int	check_valid_map(t_env *env, t_err *err)
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
				set_player_pos_dir(env, &cnt, i, j);
			if (ft_strchr("012 NEWS", env->map[i][j]) == 0)
				return (add_err_msg(err, "\nMap error, illegal characters"));
			if (env->map[i][j] == '0' && find_hole_in_map(env->map, i, j) == -1)
				return (add_err_msg(err, "\nMap error, 0 next blank or NULL"));
		}
	}
	if (cnt != 1)
		return (add_err_msg(err, "\nMap error, Problems with player location"));
	return (0);
}

int			check_valid_env(t_env *env, t_err *err) // mlx)
{
	void	*mlx;
	int		sizex;
	int		sizey;

	mlx = mlx_init();
	mlx_get_screen_size(mlx, &sizex, &sizey);
	mlx_destroy_display(mlx);
	free(mlx);
	if (env->width <= 0 || env->height <= 0)
		add_err_msg(err, "\nThe resolution value is not valid");
	if (env->width > sizex)
		env->width = sizex;
	if (env->height > sizey)
		env->height = sizey;
	if (!env->no || !env->so || !env->we || !env->ea || !env->sp)
		add_err_msg(err, "\nThere is at least 1 incomplete image path");
	check_valid_map(env, err);
	if (err->env_error > 0)
		return (-1);
	return (0);
}
