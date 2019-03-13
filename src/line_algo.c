/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 16:26:25 by tdiaz             #+#    #+#             */
/*   Updated: 2019/03/12 16:26:28 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** These functions are the workhorse in Bressenham's line algorithm. If you
** are reading this I will assume you're wondering why these functions look
** the way they do. This is because of 42 Silicon Valley's code formatting
** that restricts the number of varibles you can have and the number of lines
** in your function.
*/

#include "wire.h"

void	plotlooplow(t_mlx *mlx, int p1[2], int p2[2], int *arr)
{
	int y;
	int di;
	int dy;
	int dx;
	int yi;

	di = arr[0];
	dy = arr[1];
	yi = arr[2];
	dx = arr[3];
	y = p1[1];
	if (y > WIND_Y - 1 || y < 0)
		return ;
	while (p1[0] < p2[0])
	{
		update_img(mlx, p1[0], y);
		if (di > 0)
		{
			y = y + yi;
			di = di - 2 * dx;
		}
		di = di + 2 * dy;
		p1[0]++;
	}
}

void	plotlow(t_mlx *mlx, int p1[2], int p2[2])
{
	int dx;
	int dy;
	int yi;
	int di;
	int arr[4];

	dx = p2[0] - p1[0];
	dy = p2[1] - p1[1];
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	di = 2 * dy - dx;
	arr[0] = di;
	arr[1] = dy;
	arr[2] = yi;
	arr[3] = dx;
	plotlooplow(mlx, p1, p2, arr);
}

void	plotloophigh(t_mlx *mlx, int p1[2], int p2[2], int *arr)
{
	int x;
	int di;
	int dy;
	int dx;
	int xi;

	di = arr[0];
	dy = arr[1];
	xi = arr[2];
	dx = arr[3];
	x = p1[0];
	if (x < 0 || x > WIND_X - 1)
		return ;
	while (p1[1] < p2[1])
	{
		update_img(mlx, x, p1[1]);
		if (di > 0)
		{
			x = x + xi;
			di = di - 2 * dy;
		}
		di = di + 2 * dx;
		p1[1]++;
	}
}

void	plothigh(t_mlx *mlx, int p1[2], int p2[2])
{
	int dx;
	int dy;
	int xi;
	int di;
	int arr[4];

	dx = p2[0] - p1[0];
	dy = p2[1] - p1[1];
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	di = 2 * dx - dy;
	arr[0] = di;
	arr[1] = dy;
	arr[2] = xi;
	arr[3] = dx;
	plotloophigh(mlx, p1, p2, arr);
}
