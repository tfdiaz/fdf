/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 20:48:56 by tdiaz             #+#    #+#             */
/*   Updated: 2019/03/12 20:48:57 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** There are two transformations that must be made. First the phi then the
** theta transformation. The -/+ .5 allows us to center the image. All
** coordinate points are normalized within draw_update.c
*/

#include "wire.h"

static void	phi_transformation(t_mlx *mlx, double p1[3], double p2[3])
{
	double	phi;
	double	tmp1;
	double	tmp2;
	double	tmp3;
	double	tmp4;

	phi = mlx->phi;
	tmp1 = .5 + ((p1[0] - .5) * cos(phi) + (p1[1] - .5) * -1 * sin(phi));
	tmp2 = .5 + ((p1[0] - .5) * sin(phi) + (p1[1] - .5) * cos(phi));
	tmp3 = .5 + ((p2[0] - .5) * cos(phi) + (p2[1] - .5) * -1 * sin(phi));
	tmp4 = .5 + ((p2[0] - .5) * sin(phi) + (p2[1] - .5) * cos(phi));
	p1[0] = tmp1;
	p1[1] = tmp2;
	p2[0] = tmp3;
	p2[1] = tmp4;
}

static void	theta_transformation(t_mlx *mlx, double p1[3], double p2[3],
									double *pt)
{
	double theta;

	theta = mlx->theta;
	pt[0] = mlx->f_len * (p1[0] - .5) /
		(mlx->zoom + (.5 - p1[1]) * sin(theta)) + .5;
	pt[1] = .5 - ((mlx->f_len * (((.5 - p1[1])) * cos(theta)
		+ (sin(theta) * (p1[2]))) /
			(mlx->zoom + (.5 - p1[1]) * sin(theta))));
	pt[2] = mlx->f_len * (p2[0] - .5) /
		(mlx->zoom + (.5 - p2[1]) * sin(theta)) + .5;
	pt[3] = .5 - ((mlx->f_len * (((.5 - p2[1])) * cos(theta)
		+ (sin(theta) * (p2[2]))) /
			(mlx->zoom + (.5 - p2[1]) * sin(theta))));
}

double		*projection(t_mlx *mlx, double p1[3], double p2[3])
{
	double	*pt;

	pt = (double *)malloc(sizeof(double) * 4);
	phi_transformation(mlx, p1, p2);
	theta_transformation(mlx, p1, p2, pt);
	return (pt);
}
