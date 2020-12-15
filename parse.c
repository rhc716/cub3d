/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 15:28:44 by hroh              #+#    #+#             */
/*   Updated: 2020/12/15 14:12:22 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	parse_map(char *line, t_env *env)
{
	int		len;
	int		i;
	char	**temp;

	env->row++;
	i = 0;
	temp = (char **)malloc(sizeof(char *) * (env->row + 1));
	temp[env->row] = 0;
	while (env->row > 1 && env->map[i])
	{
		temp[i] = env->map[i];
		i++;
	}
	temp[env->row - 1] = ft_strdup(line);
	free(env->map);
	env->map = temp;
	len = ft_strlen(line);
	if (env->col < len)
		env->col = len;
}

static void	parse_path(char *line, t_env *env, t_err *err)
{
	char	*path;
	char	**env_set;

	path = &line[3];
	if (line[0] == 'S' && line[1] == ' ')
		path = &line[2];
	if (line[0] == 'N' && line[1] == 'O')
		env_set = &env->no;
	else if (line[0] == 'S' && line[1] == 'O')
		env_set = &env->so;
	else if (line[0] == 'W' && line[1] == 'E')
		env_set = &env->we;
	else if (line[0] == 'E' && line[1] == 'A')
		env_set = &env->ea;
	else if (line[0] == 'S' && line[1] == ' ')
		env_set = &env->sp;
	if (*env_set == NULL)
	{
		*env_set = ft_strdup(path);
		if (!check_valid_path(path))
			add_err_msg(err, "\nThe path of the image is not valid");
	}
	else
		add_err_msg(err, "\nDouble setting values exist");
}

static void	parse_color(char *s, t_env *env, t_err *err)
{
	char	**temp;
	int		i;
	int		j;

	temp = ft_split(&s[2], ',');
	i = 0;
	while (temp[i])
		i++;
	if (i != 3 || (s[0] == 'F' && env->floor) || (s[0] == 'C' && env->ceiling))
		add_err_msg(err, "\nThe color of the floor or ceiling is not valid");
	i = 0;
	while (temp[i])
	{
		if (ft_atoi(temp[i]) > 255 || ft_atoi(temp[i]) < 0)
			add_err_msg(err, "\nColor value exceeds the range.");
		j = 0;
		while (temp[i][j])
			if (!ft_isdigit(temp[i][j++]))
				add_err_msg(err, "\nColor value has a non-digit value.");
		if (s[0] == 'F')
			env->floor = env->floor * 256 + ft_atoi(temp[i++]);
		else
			env->ceiling = env->ceiling * 256 + ft_atoi(temp[i++]);
	}
	free_2d_array(temp);
}

static void	parse_width_height(char *line, t_env *env, t_err *err)
{
	if (env->width || env->height)
	{
		add_err_msg(err, "\nDouble setting values exist");
		return ;
	}
	env->width = ft_atoi(&line[2]);
	env->height = ft_atoi(&line[2 + ft_nbrlen(env->width)]);
}

void		parse_env(char *line, t_env *env, t_err *err)
{
	if (line[0] == 0)
	{
		if (env->map != NULL)
			add_err_msg(err, "\nEmpty line in the middle of the map");
		return ;
	}
	else if (line[0] == 'R' && line[1] == ' ')
		parse_width_height(line, env, err);
	else if ((line[0] == 'N' && line[1] == 'O')
		|| (line[0] == 'S' && line[1] == 'O')
		|| (line[0] == 'W' && line[1] == 'E')
		|| (line[0] == 'E' && line[1] == 'A')
		|| (line[0] == 'S' && line[1] == ' '))
	{
		parse_path(line, env, err);
	}
	else if ((line[0] == 'F' || line[0] == 'C') && line[1] == ' ')
	{
		if ((line[0] == 'F' && env->floor != 0)
		|| (line[0] == 'C' && env->ceiling != 0))
			add_err_msg(err, "\nDouble setting values exist");
		else
			parse_color(line, env, err);
	}
	else
		parse_map(line, env);
}
