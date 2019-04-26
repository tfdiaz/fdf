/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 16:48:00 by tdiaz             #+#    #+#             */
/*   Updated: 2018/09/17 16:48:01 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The goal of this program is to take a textfile which describes a wireframe,
** and project that frame to create 3-D images. This program uses minilibx,
** which is a very simple graphics library that allows one to place pixels on
** a window. The core of this project is in projection.c file, which allows
** one to take three points and place them correctly in a 2-D space given two
** angles, camera distance, and focal length.
*/

#include "wire.h"

void	build(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIND_X, WIND_Y,
	"Wire Machine by Tomas Diaz");
	draw_update(mlx);
	mlx_hook(mlx->win_ptr, 2, 0, key_press, (void*)mlx);
	mlx_hook(mlx->win_ptr, 3, 0, key_press, (void*)mlx);
	mlx_hook(mlx->win_ptr, 17, 0, closes, (void*)mlx);
	mlx_loop(mlx->mlx_ptr);
}

t_mlx	*constructor(void)
{
	t_mlx	*mlx;

	mlx = (t_mlx*)malloc(sizeof(t_mlx));
	mlx->y_len = 0;
	mlx->x_len = 0;
	mlx->z_len = 0;
	mlx->theta = 0.0;
	mlx->phi = 0.0;
	mlx->z_shift = 0;
	mlx->zoom = 1.5;
	mlx->f_len = .8;
	mlx->xy_shift = 0;
	mlx->color_mode = 1;
	return (mlx);
}

int		main(int argc, char **argv)
{
	t_mlx	*mlx;

	if (argc == 2)
	{
		mlx = constructor();
		read_file(open(argv[1], O_RDONLY), mlx, 1, 1);
		build(mlx);
	}
	else
		ft_printf("Error in input. Try ./fdf <nameofmap.fdf>\n");
	return (0);
}
