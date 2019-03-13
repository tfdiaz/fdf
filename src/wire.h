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

# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <fcntl.h>
# include <math.h>

# define WIND_X 1200
# define WIND_Y 1200
# define CAM_DIST 1
# define F_LEN .8
# define SPEED .03

# define KEY_ESC 53
# define KEY_UP_ARROW 126
# define KEY_DOWN_ARROW 125
# define KEY_LEFT_ARROW 123
# define KEY_RIGHT_ARROW 124
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_R 15
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_MIN 27
# define KEY_PLUS 24
# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_THREE 20

typedef unsigned int	t_color;

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*image;
	char	*address;
	int		**data;
	int		bpp;
	int		sl;
	int		x_len;
	int		y_len;
	int		z_len;
	int		color_mode;
	double	z_shift;
	double	xy_shift;
	double	theta;
	double	phi;
	double	zoom;
	double	f_len;
	t_color	color;
}				t_mlx;

void			draw_update(t_mlx *mlx);
void			theta_shift(char type, t_mlx *mlx);
void			phi_shift(char type, t_mlx *mlx);
void			z_shift(char type, t_mlx *mlx);
void			zoom_shift(char type, t_mlx *mlx);
void			focal_shift(char type, t_mlx *mlx);
void			reset(t_mlx *mlx);
void			destroy(t_mlx *mlx);
void			color_shift(char type, t_mlx *mlx);
void			xy_shift(char type, t_mlx *mlx);
int				key_press(int keycode, void *param);
void			plothigh(t_mlx *mlx, int p1[2], int p2[2]);
void			plotlow(t_mlx *mlx, int p1[2], int p2[2]);
void			update_img(t_mlx *mlx, int x, int y);
int				strslen(char **strs);
int				closes(void *param);
void			read_file(int fd, t_mlx *mlx, int i);
void			freestrs(char ***strs);
void			close_and_free(char *line, int fd);
void			init_data(int ***ret, int **row, int i, t_mlx *mlx);
void			error_in_read(int fd);
void			draw_line(t_mlx *mlx, double d_p1[3], double d_p2[3]);
double			*projection(t_mlx *mlx, double p1[3], double p2[3]);
unsigned int	set_color(t_mlx *mlx, double p1[3], double p2[3]);

#endif
