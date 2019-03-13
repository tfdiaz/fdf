/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 20:20:41 by tdiaz             #+#    #+#             */
/*   Updated: 2019/03/12 20:20:42 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** draw_line(t_mlx *mlx, double d_p1[3], double d_p2[3]) will first project the
** xyz points in 2-D space. We will round this points to fit our given window.
** We will then check that these points are in our window. If they are not, we
** don't want to waste time rendering it. We will then apply Bressenham's line
** algorithm. Functions: plotlow and plothigh are found in line_algo.c
*/

#include "wire.h"

static void	round_projection(double *pt, int *p1, int *p2)
{
	p1[0] = round(pt[0] * WIND_X);
	p1[1] = round(pt[1] * WIND_Y);
	p2[0] = round(pt[2] * WIND_X);
	p2[1] = round(pt[3] * WIND_Y);
}

static char	bool_check_out_of_bounds(int *p1, int *p2)
{
	if ((p1[0] < 0 || p1[0] > WIND_X - 1) &&
		(p2[0] < 0 || p2[0] > WIND_X - 1))
		return (1);
	if ((p1[1] < 0 || p1[1] > WIND_Y - 1) &&
		(p2[1] < 0 || p2[1] > WIND_Y - 1))
		return (1);
	return (0);
}

void		draw_line(t_mlx *mlx, double d_p1[3], double d_p2[3])
{
	t_color	color;
	double	*pt;
	int		p1[2];
	int		p2[2];

	mlx->color = set_color(mlx, d_p1, d_p2);
	pt = projection(mlx, d_p1, d_p2);
	round_projection(pt, p1, p2);
	if (bool_check_out_of_bounds(p1, p2))
		return ;
	if (abs(p2[1] - p1[1]) < abs(p2[0] - p1[0]))
	{
		if (p1[0] > p2[0])
			plotlow(mlx, p2, p1);
		else
			plotlow(mlx, p1, p2);
	}
	else
	{
		if (p1[1] > p2[1])
			plothigh(mlx, p2, p1);
		else
			plothigh(mlx, p1, p2);
	}
	free(pt);
}
