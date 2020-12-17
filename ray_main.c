/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 17:17:38 by hroh              #+#    #+#             */
/*   Updated: 2020/12/18 02:59:48 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		to_coord(double x, double y, t_env *env)
{
	return ((int)floor(y) * env->width + (int)floor(x));
}

void	draw_line(t_env *env, double x1, double y1, double x2, double y2)
{
	double	deltaX;
	double	deltaY;
	double	step;

	deltaX = x2 - x1;
	deltaY = y2 - y1;
	step = (fabs(deltaX) > fabs(deltaY)) ? fabs(deltaX) : fabs(deltaY);
	deltaX /= step;
	deltaY /= step;
	while (fabs(x2 - x1) > 0.01 || fabs(y2 - y1) > 0.01)
	{
		env->ray->img->data[to_coord(x1, y1, env)] = 0x00b3b3;
		x1 += deltaX;
		y1 += deltaY;
	}
}

void 	draw_lines(t_env *env)
{
	int		i;
	int		j;
	double	ts_x;
	double	ts_y;

	i = 0;
	ts_x = env->ray->tilesize_x;
	ts_y = env->ray->tilesize_y;
	while (i * ts_x < env->width)
	{
		draw_line(env, i * ts_x, 0, i * ts_x, env->height);
		i++;
	}
	draw_line(env, env->col * ts_x - 1, 0, env->col * ts_x - 1, env->height);
	j = 0;
	while (j * ts_y < env->height)
	{
		draw_line(env, 0, j * ts_y, env->width, j * ts_y);
		j++;
	}
	draw_line(env, 0, env->row * ts_y - 1, env->width, env->row * ts_y - 1);
}

void	draw_block(t_env *env, int x, int y, int color)
{
	int		i;
	int		j;
	t_ray	*ray;

	ray = env->ray;
	x *= ray->tilesize_x;
	y *= ray->tilesize_y;
	i = 0;
	while (i < ray->tilesize_y)
	{
		j = 0;
		while (j < ray->tilesize_x)
		{
			env->ray->img->data[(y + i) * env->width + x + j] = color;
			j++;
		}
		i++;
	}
}

void	draw_map(t_env *env)
{
	int		i;
	int		j;

	i = 0;
	while (env->map[i])
	{
		j = 0;
		while (env->map[i][j])
		{
			if (env->map[i][j] == '1')
				draw_block(env, j, i, 0x000080);
			j++;
		}
		i++;
	}
}

int 	ft_close(t_env *env)
{
	free_all(env);
	exit(0);
}

int		deal_key(int key_code, t_env *env)
{
	t_ray *ray;
	double oldDirX;
	double oldPlaneX;

	ray = env->ray;
	if (key_code == KEY_ESC)
		ft_close(env);
	if (key_code == KEY_UP || key_code == KEY_W)
    {
    	if(env->map[(int)(ray->posX + ray->dirX * 0.05)][(int)ray->posY] == '0')
			ray->posX += ray->dirX * 0.05;
    	if(env->map[(int)ray->posX][(int)(ray->posY + ray->dirY * 0.05)] == '0')
			ray->posY += ray->dirY * 0.05;
    }
    if (key_code == KEY_DOWN || key_code == KEY_S)
    {
		if(env->map[(int)(ray->posX - ray->dirX * 0.05)][(int)ray->posY] == '0')
			ray->posX -= ray->dirX * 0.05;
    	if(env->map[(int)ray->posX][(int)(ray->posY - ray->dirY * 0.05)] == '0')
			ray->posY -= ray->dirY * 0.05;
    }
    if (key_code == KEY_RIGHT || key_code == KEY_D)
    {
		oldDirX = ray->dirX;
		ray->dirX = ray->dirX * cos(-0.05) - ray->dirY * sin(-0.05);
		ray->dirY = oldDirX * sin(-0.05) + ray->dirY * cos(-0.05);
		oldPlaneX = ray->planeX;
		ray->planeX = ray->planeX * cos(-0.05) - ray->planeY * sin(-0.05);
		ray->planeY = oldPlaneX * sin(-0.05) + ray->planeY * cos(-0.05);
    }
    if (key_code == KEY_LEFT || key_code == KEY_A)
    {
		oldDirX = ray->dirX;
		ray->dirX = ray->dirX * cos(0.05) - ray->dirY * sin(0.05);
		ray->dirY = oldDirX * sin(0.05) + ray->dirY * cos(0.05);
		oldPlaneX = ray->planeX;
		ray->planeX = ray->planeX * cos(0.05) - ray->planeY * sin(0.05);
		ray->planeY = oldPlaneX * sin(0.05) + ray->planeY * cos(0.05);
    }
	//printf("cameraX : %f \n", ray->cameraX);
	//printf("rayDirX : %f \n", ray->rayDirX);
	//printf("rayDirY : %f \n", ray->rayDirY);
	//printf("testv : %d \n", ray->testv);
	//printf("hit : %d \n", ray->hit);
	//printf("perpWallDist : %f \n", ray->perpWallDist);
	printf("posX : %f, posY : %f \n", ray->posX, ray->posY);
	printf("dirX : %f, dirY : %f \n", ray->dirX, ray->dirY);
	return (0);
}

void	ray_init(t_ray *ray, t_env *env)
{
	ray->mlx = mlx_init();
	printf("posX : %f, posY : %f \n", ray->posX, ray->posY);
	printf("dirX : %f, dirY : %f \n", ray->dirX, ray->dirY);
	printf("ray->tilesize_x : %f \n", ray->tilesize_x);
	printf("ray->tilesize_y : %f \n", ray->tilesize_y);
	printf("(int)(ray->posY * ray->tilesize_x) : %d \n", (int)(ray->posY * ray->tilesize_x));
	ray->win = mlx_new_window(ray->mlx, env->width, env->height, "cub3d");
	ray->img->img = mlx_new_image(ray->mlx, env->width, env->height);
	ray->img->data = (int *)mlx_get_data_addr(ray->img->img, &ray->img->bpp, &ray->img->size_l, &ray->img->endian);
}

void	draw_player(t_env *env)
{
	t_ray	*ray;
	int		i;
	int		j;

	ray = env->ray;
	i = -1;
	while (++i < 7)
	{
		j = -1;
		while (++j < 7)
			ray->img->data[((int)ray->posX * (int)ray->tilesize_y + i) * env->width + (int)ray->posY * (int)ray->tilesize_x + j] = 0xFFFF66;
	}
}

void	draw_background(t_env *env)
{
	int i;
	int j;
	
	i = -1;
	while (++i < env->height)
	{
		j = -1;
		while (++j < env->width)
			env->ray->img->data[i * env->width + j] = 0x000000;
	}
}

int		main_loop(t_env *env)
{
	draw_background(env);
	//draw_map(env);
	//draw_lines(env);
	//draw_player(env);
	ray_main_loop(env);
	mlx_put_image_to_window(env->ray->mlx, env->ray->win, env->ray->img->img, 0, 0);
	return (0);
}

int	ray_caster(t_env *env, t_err *err, int c)
{
	t_ray *ray;

	if (!(ray = (t_ray *)malloc(sizeof(t_ray))) || !init_ray(ray, env))
		return (add_err_msg(err, "malloc error"));
	if (c == 2)
	{
		write(1, "screen shot!!\n", 14);
		return (0);
	}
	ray_init(ray, env);
	mlx_hook(ray->win, X_EVENT_KEY_PRESS, KeyPressMask, &deal_key, env);
	mlx_hook(ray->win, X_EVENT_RED_CROSS, 1<<17, &ft_close, env);
	mlx_loop_hook(ray->mlx, &main_loop, env);
	mlx_loop(ray->mlx);
	return (0);
}
