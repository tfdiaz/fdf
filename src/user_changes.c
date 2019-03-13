/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_changes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 16:06:45 by tdiaz             #+#    #+#             */
/*   Updated: 2019/03/12 16:06:46 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** See comments from keypress.c and user_shifts.c
*/

#include "wire.h"

void	reset(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->image);
	mlx->phi = M_PI_4;
	mlx->theta = M_PI_4;
	mlx->z_shift = 0.5;
	mlx->f_len = 0.8;
	mlx->xy_shift = 0;
	mlx->zoom = 1.5;
	draw_update(mlx);
}

void	destroy(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	exit(0);
}

void	color_shift(char type, t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->image);
	mlx->color_mode = (int)type;
	draw_update(mlx);
}

void	xy_shift(char type, t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->image);
	if (type)
	{
		mlx->xy_shift += SPEED;
		if (mlx->xy_shift > 1.0)
			mlx->xy_shift = 1.0;
	}
	else
	{
		mlx->xy_shift -= SPEED;
		if (mlx->xy_shift < -1.0)
			mlx->xy_shift = -1.0;
	}
	draw_update(mlx);
}
