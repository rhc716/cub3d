/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 15:51:24 by hroh              #+#    #+#             */
/*   Updated: 2020/12/15 17:49:34 by hroh             ###   ########.fr       */
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

# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_EXIT	17
# define KEY_ESC			65307
# define KeyPressMask		(1L<<0)

typedef struct	s_err
{
	int			env_error;
	char		*env_error_msg;
}				t_err;

typedef struct	s_img
{
	void		*img;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_ray
{
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	double		time;
	double		oldtime;
	double		tilesize_x;
	double		tilesize_y;
	void		*mlx;
	void		*win;
	t_img		*img;
}				t_ray;

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
	double		posX_init;
	double		posY_init;
	double		dirX_init;
	double		dirY_init;
	t_ray		*ray;
}				t_env;

void			parse_env(char *line, t_env *env, t_err *err);
void			free_2d_array(char **array);
int				check_valid_path(char *path);
int				free_all(t_env *env);
int				print_error_exit(t_err *err, t_env *env, char *str);
int				add_err_msg(t_err *err, char *str);
int				check_valid_path(char *path);
int				check_valid_env(t_env *env, t_err *err);
int				init_env(t_env **env);
int				init_ray(t_ray *ray, t_env *env);
void			init_error(t_err *err);
int				ray_caster(t_env *env, t_err *err, int c);

#endif
