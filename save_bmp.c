/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 17:51:52 by hroh              #+#    #+#             */
/*   Updated: 2020/12/23 22:34:49 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_progress_bar(int i, int height)
{
	int		k;
	double	n;

	k = 0;
	n = 0.1;
	write(1, "\rProgress : [", 13);
	while (n < 1)
	{
		if (i <= height * (1.0 - n) && i > height * (0.9 - n))
		{
			k = n * 10 - 1;
			break ;
		}
		n += 0.1;
	}
	if (i == 0)
		k = 10;
	write(1, "**********", k);
	write(1, "          ", 10 - k);
	write(1, "]", 1);
	if (k == 10)
		write(1, "\nComplete!\n", 11);
}

void	set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

void	write_header(t_env *env, int fd, int size)
{
	unsigned char		header[54];

	ft_memset(header, 0, 54);
	header[0] = (unsigned char)'B';
	header[1] = (unsigned char)'M';
	set_int_in_char(header + 2, size);
	header[10] = (unsigned char)54;
	header[14] = (unsigned char)40;
	set_int_in_char(header + 18, env->width);
	set_int_in_char(header + 22, env->height);
	header[26] = (unsigned char)1;
	header[28] = (unsigned char)24;
	write(fd, header, 54);
}

void	write_body(t_env *env, int fd)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					i;
	int					j;
	int					pad;

	i = env->height;
	pad = (4 - (env->width * 3) % 4) % 4;
	while (--i >= 0)
	{
		j = -1;
		while (++j < env->width)
		{
			write(fd, &env->ray->img->data[i * env->width + j], 3);
		}
		if (pad > 0)
			write(fd, &zero, pad);
		print_progress_bar(i, env->height);
	}
}

int		save_bmp(t_env *env)
{
	int					fd;
	int					size;

	size = 54 + 3 * env->width * env->height;
	if ((fd = open("./save.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 00755)) < 0)
		return (-1);
	write_header(env, fd, size);
	write_body(env, fd);
	return (1);
}
