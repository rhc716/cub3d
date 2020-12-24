/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 15:51:24 by hroh              #+#    #+#             */
/*   Updated: 2020/12/24 20:58:32 by hroh             ###   ########.fr       */
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
# define KEY_1				49
# define KEY_W				119
# define KEY_S				115
# define KEY_A				97
# define KEY_D				100
# define KEY_LEFT			65361
# define KEY_RIGHT			65363
# define KEY_TAB			65289
# define KEY_PRESS_MASK		1

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
	int			width;
	int			height;
}				t_img;

typedef struct	s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef struct	s_sprite
{
	double		x;
	double		y;
	double		dist;
}				t_sprite;

typedef struct	s_sprite_env
{
	double		sprite_x;
	double		sprite_y;
	double		invdet;
	double		trs_x;
	double		trs_y;
	int			sprite_screen_x;
	int			sprite_h;
	int			sprite_w;
	int			draw_start_y;
	int			draw_end_y;
	int			draw_start_x;
	int			draw_end_x;
	int			vdiv;
	double		vmove;
}				t_sp_env;

typedef struct	s_ray
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		camerax;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	double		perpwalldist;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	double		tilesize_x;
	double		tilesize_y;
	void		*mlx;
	void		*win;
	t_img		*img;
	double		movespeed;
	double		rotspeed;
	int			line_h;
	int			drawstart;
	int			drawend;
	int			**texture;
	t_pos		*texture_size;
	t_sprite	*sprite;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	int			texnum;
	double		tex_pos;
	double		tex_pos_x;
	double		*zbuffer;
	t_sp_env	*sp_env;
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
	double		posx_init;
	double		posy_init;
	double		dirx_init;
	double		diry_init;
	int			sprite_cnt;
	int			tex_cnt;
	int			map_mode;
	int			night_mode;
	double		x2;
	double		y2;
	t_ray		*ray;
}				t_env;

void			parse_env(char *line, t_env *env, t_err *err);
void			free_2d_array(void **array, int len);
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
void			ray_loop(t_env *env, t_ray *ray);
void			draw_map(t_env *env);
void			draw_lines(t_env *env, double tx, double ty);
void			draw_line(t_env *env, double x1, double y1);
void			draw_background(t_env *env, int c);
void			draw_player(t_env *env, int color);
void			draw_map_ray(t_env *env, t_ray *ray, int x);
int				deal_key(int key_code, t_env *env);
int				ft_close(t_env *env);
int				load_texture(t_env *env, t_ray *ray, t_err *err);
void			save_sprite_xy(t_env *env);
void			draw_sprite(t_env *env, t_ray *ray);
int				save_bmp(t_env *env);

#endif
