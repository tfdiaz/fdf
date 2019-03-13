/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 09:52:01 by tdiaz             #+#    #+#             */
/*   Updated: 2019/03/13 09:52:03 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Miscellaneous functions that are called throughout but need to be separated
** out because of 42 Silicon Valley's rules.
*/

#include "wire.h"

int				closes(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx*)param;
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	exit(0);
	return (0);
}

int				strslen(char **strs)
{
	int i;

	i = 0;
	while (*strs)
	{
		i++;
		strs++;
	}
	return (i);
}

void			freestrs(char ***strs)
{
	int i;

	i = 0;
	while ((*strs)[i] != NULL)
	{
		free((*strs)[i]);
		i++;
	}
	free(*strs);
	*strs = NULL;
}

unsigned int	set_color(t_mlx *mlx, double p1[3], double p2[3])
{
	double	average;
	int		shift;

	if (mlx->color_mode == 3)
	{
		average = (p1[2] + p2[2]) / 2.0;
		shift = average * 70000;
		return (mlx_get_color_value(mlx->mlx_ptr, 0x010000 + shift));
	}
	else if (mlx->color_mode == 2)
	{
		average = (p1[2] + p2[2]) / 2.0;
		shift = (1 - average) * 13;
		shift <<= 20;
		return (mlx_get_color_value(mlx->mlx_ptr, 0xFF0000 - shift));
	}
	else
		return (mlx_get_color_value(mlx->mlx_ptr, 0x00FFFF));
}

void			update_img(t_mlx *mlx, int x, int y)
{
	int	j;

	j = 0;
	if (x > WIND_X - 1 || y > WIND_Y - 1 || y < 0 || x < 0)
		return ;
	while (j < mlx->bpp / 8)
	{
		*(mlx->address + (mlx->sl * y + mlx->bpp * x / 8 + j)) =
			(mlx->color >> (8 * j)) & 0xFF;
		j++;
	}
}
