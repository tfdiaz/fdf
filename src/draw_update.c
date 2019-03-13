/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 20:33:55 by tdiaz             #+#    #+#             */
/*   Updated: 2019/03/12 20:33:56 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
** These functions will iterate through all the points in our wireframe. These
** points are stored in mlx->data. We will call y_to_x_loop and x_to_y_loop to
** draw lines from each point to its neighbors. Prior to this we will call
** minilibx's functions to create a new image and end with place image on the
** window. More information can be found in the minilibx_macos/man.
*/

#include "wire.h"

static void	y_to_x_loop(t_mlx *mlx)
{
	int		y;
	int		x;
	int		**data;
	double	p1[3];
	double	p2[3];

	y = 0;
	data = mlx->data;
	while (y < mlx->y_len)
	{
		x = 0;
		while (x + 1 < mlx->x_len)
		{
			p1[0] = (double)x / mlx->x_len + mlx->xy_shift;
			p1[1] = (double)y / mlx->y_len + mlx->xy_shift;
			p1[2] = (double)data[y][x] / mlx->z_len * mlx->z_shift;
			p2[0] = (double)(x + 1) / mlx->x_len + mlx->xy_shift;
			p2[1] = (double)y / mlx->y_len + mlx->xy_shift;
			p2[2] = (double)data[y][x + 1] / mlx->z_len * mlx->z_shift;
			draw_line(mlx, p1, p2);
			x++;
		}
		y++;
	}
}

static void	x_to_y_loop(t_mlx *mlx)
{
	int		y;
	int		x;
	int		**data;
	double	p1[3];
	double	p2[3];

	x = 0;
	data = mlx->data;
	while (x < mlx->x_len)
	{
		y = 0;
		while (y + 1 < mlx->y_len)
		{
			p1[0] = (double)x / mlx->x_len + mlx->xy_shift;
			p1[1] = (double)y / mlx->y_len + mlx->xy_shift;
			p1[2] = (double)data[y][x] / mlx->z_len * mlx->z_shift;
			p2[0] = (double)x / mlx->x_len + mlx->xy_shift;
			p2[1] = (double)(y + 1) / mlx->y_len + mlx->xy_shift;
			p2[2] = (double)data[y + 1][x] / mlx->z_len * mlx->z_shift;
			draw_line(mlx, p1, p2);
			y++;
		}
		x++;
	}
}

void		draw_update(t_mlx *mlx)
{
	int bpp;
	int red;
	int size_line;
	int endian;

	mlx->image = mlx_new_image(mlx->mlx_ptr, WIND_X, WIND_Y);
	mlx->address = mlx_get_data_addr(mlx->image, &bpp, &size_line, &endian);
	mlx->bpp = bpp;
	mlx->sl = size_line;
	y_to_x_loop(mlx);
	x_to_y_loop(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->image, 0, 0);
}
