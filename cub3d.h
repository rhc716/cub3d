/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 15:51:24 by hroh              #+#    #+#             */
/*   Updated: 2020/12/19 21:35:17 by hroh             ###   ########.fr       */
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
# define X_EVENT_RED_CROSS	33
# define KEY_ESC			65307
# define KEY_W				119
# define KEY_S				115
# define KEY_A				97
# define KEY_D				100
# define KEY_LEFT			65361
# define KEY_RIGHT			65363
# define KEY_TAB			65289
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
	double		cameraX;
	double		rayDirX;
	double		rayDirY;
	int			mapX;
	int			mapY;
	double		sideDistX;
    double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	double		perpWallDist;
	int			stepX;
    int			stepY;
	int			hit;
    int			side;
	double		tilesize_x;
	double		tilesize_y;
	void		*mlx;
	void		*win;
	t_img		*img;
	int			map_on;
	double		moveSpeed;
	double		rotSpeed;
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
void			ray_main_loop(t_env *env);
void			draw_map(t_env *env);
void		 	draw_lines(t_env *env);
void			draw_line(t_env *env, double x1, double y1, double x2, double y2);
void			draw_background(t_env *env, int c);
int				deal_key(int key_code, t_env *env);
int 			ft_close(t_env *env);
#endif
