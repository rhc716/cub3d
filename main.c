/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 18:09:34 by hroh              #+#    #+#             */
/*   Updated: 2020/12/15 16:42:31 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		test_print(t_env *env)
{
	int i;

	printf("~~parsing result~~\n");
	printf("width : %d, height : %d\n", env->width, env->height);
	printf("NO : %s\n", env->no);
	printf("SO : %s\n", env->so);
	printf("WE : %s\n", env->we);
	printf("EA : %s\n", env->ea);
	printf("SPRITE : %s\n", env->sp);
	printf("FLOOR : %d\n", env->floor);
	printf("CEILING : %d\n", env->ceiling);
	printf("\n\n~~~map~~~\n\n");
	i = 0;
	while (env->map[i])
		printf("%s\n", env->map[i++]);
	printf("row : %d\n", env->row);
	printf("col max : %d\n", env->col);
	printf("player posX : %f\n", env->posX_init);
	printf("player posY : %f\n", env->posY_init);
	printf("player dirX : %f\n", env->dirX_init);
	printf("player dirY : %f\n", env->dirY_init);
}

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
	//test_print(env);
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
		if (read_file(argv[1], env, &err) == -1)
			return (print_error_exit(&err, env, ""));
		if (argc == 2)
			ray_caster(env, &err, 1);
		else
			ray_caster(env, &err, 2);
	}
	return (free_all(env));
}
