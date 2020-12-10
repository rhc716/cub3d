/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 18:09:34 by hroh              #+#    #+#             */
/*   Updated: 2020/12/10 19:01:10 by hroh             ###   ########.fr       */
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
}

static int	read_file(char *file, t_env *env)
{
	int		fd;
	char	*line;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (add_err_msg(env, "\nFailed to open the file."));
	while (get_next_line(fd, &line) > 0)
	{
		parse_env(line, env);
		free(line);
		line = NULL;
	}
	parse_env(line, env);
	free(line);
	test_print(env);
	if (check_valid_env(env) == -1)
		return (-1);
	return (0);
}

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
	env->env_error = 0;
	env->env_error_msg = NULL;
}

int			main(int argc, char **argv)
{
	t_env *env;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		return (print_error(env, "malloc error"));
	init_env(env);
	if ((argc < 2 || argc > 3) ||
		(argc == 3 && ft_strncmp(argv[2], "--save", 6) != 0))
		return (print_error(env, "main function input value error"));
	else if (argc == 3)
	{
		write(1, "screen shot!\n", 13);
		return (0);
	}
	if (argc == 2)
	{
		if (read_file(argv[1], env) == -1)
		{
			print_error(env, "");
			return (free_all(env));
		}
		free_all(env); // 임시
		return (0);
	}
	return (0);
}
