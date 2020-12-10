/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 15:51:24 by hroh              #+#    #+#             */
/*   Updated: 2020/12/10 19:23:05 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include "./lib/minilibx-linux/mlx.h"
# include "./lib/libft/libft.h"

typedef struct	s_env
{
	int			width;
	int			height;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*sp;
	char		**map;
	int			floor;
	int			ceiling;
	int			row;
	int			col;
	int			env_error;
	char		*env_error_msg;
}				t_env;

void			parse_env(char *line, t_env *env);
void			free_2d_array(char **array);
int				check_valid_path(char *path);
int				free_all(t_env *env);
int				print_error(t_env *env, char *str);
int				add_err_msg(t_env *env, char *str);
int				check_valid_path(char *path);
int				check_valid_env(t_env *env);

#endif
