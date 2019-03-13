/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 16:01:56 by tdiaz             #+#    #+#             */
/*   Updated: 2019/03/12 16:02:10 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Minilibx comes with hooks to grab certain keypresses. The functions below
** map keys to individual actions. All additional functions can be found in
** user_changes.c and user_shifts.c
*/

#include "wire.h"

static void	key_press_helper(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_PLUS)
		focal_shift(1, mlx);
	if (keycode == KEY_MIN)
		focal_shift(0, mlx);
	if (keycode == KEY_ESC)
		destroy(mlx);
	if (keycode == KEY_UP_ARROW)
		theta_shift(1, mlx);
	if (keycode == KEY_DOWN_ARROW)
		theta_shift(0, mlx);
	if (keycode == KEY_RIGHT_ARROW)
		phi_shift(1, mlx);
	if (keycode == KEY_LEFT_ARROW)
		phi_shift(0, mlx);
}

int			key_press(int keycode, void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx*)param;
	if (keycode > KEY_TWO)
		key_press_helper(keycode, mlx);
	if (keycode == KEY_R)
		reset(mlx);
	if (keycode == KEY_E)
		z_shift(1, mlx);
	if (keycode == KEY_Q)
		z_shift(0, mlx);
	if (keycode == KEY_W)
		zoom_shift(1, mlx);
	if (keycode == KEY_S)
		zoom_shift(0, mlx);
	if (keycode == KEY_D)
		xy_shift(1, mlx);
	if (keycode == KEY_A)
		xy_shift(0, mlx);
	if (keycode == KEY_ONE)
		color_shift(1, mlx);
	if (keycode == KEY_TWO)
		color_shift(2, mlx);
	return (1);
}
