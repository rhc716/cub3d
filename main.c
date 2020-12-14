/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 18:09:34 by hroh              #+#    #+#             */
/*   Updated: 2020/12/14 22:07:34 by hroh             ###   ########.fr       */
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
	if (check_valid_env(env) == -1)
		return (-1);
	test_print(env);
	return (0);
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
	else if (argc == 3 && ft_strncmp(argv[2], "--save", 6) == 0)
		return (write(1, "screen shot!\n", 13));
	if (argc == 2)
	{
		if (read_file(argv[1], env) == -1)
		{
			print_error(env, "");
			return (free_all(env));
		}
		//ray_caster(env);
		free_all(env); // 임시
	}
	return (0);
}
