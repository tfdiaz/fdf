/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wire.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 16:48:22 by tdiaz             #+#    #+#             */
/*   Updated: 2018/09/17 16:48:24 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WIRE_H
# define WIRE_H

# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include <fcntl.h>
# include <math.h>

#define WIND_X 1200
#define WIND_Y 1200
#define CAM_DIST 2
#define F_LEN .8

typedef unsigned int t_color;

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*image;
	char	*address;
	int		bpp;
	int		sl;
	int		x_len;
	int		y_len;
	int		z_len;
	t_color color;
}				t_mlx;
#endif

