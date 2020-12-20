/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 18:09:34 by hroh              #+#    #+#             */
/*   Updated: 2020/12/20 21:03:41 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	read_file(char *file, t_env *env, t_err *err)
{
	int		fd;
	char	*line;
	int		ret;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (add_err_msg(err, "\nFailed to open the file."));
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		parse_env(line, env, err);
		free(line);
		line = NULL;
	}
	if (ret == -1)
		return (add_err_msg(err, "\nFailed to get the line"));
	parse_env(line, env, err);
	free(line);
	if (check_valid_env(env, err) == -1)
		return (-1);
	return (0);
}

int			main(int argc, char **argv)
{
	t_env *env;
	t_err err;

	env = NULL;
	init_error(&err);
	if (!init_env(&env))
		return (print_error_exit(&err, env, "malloc error"));
	if ((argc < 2 || argc > 3 || (argc == 3 && ft_strlen(argv[2]) != 6)) ||
		(argc == 3 && ft_strncmp(argv[2], "--save", 6) != 0))
		return (print_error_exit(&err, env, "main() input option error"));
	if (argc == 2 || (argc == 3 && !ft_strncmp(argv[2], "--save", 6)))
	{
		if (read_file(argv[1], env, &err) == -1 || err.env_error > 0)
			return (print_error_exit(&err, env, ""));
		if (ray_caster(env, &err, argc) == -1 || err.env_error > 0)
			return (print_error_exit(&err, env, ""));
	}
	return (free_all(env));
}
