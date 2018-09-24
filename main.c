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

#include "wire.h"

int key_press(int keycode, void *param)
{
	t_mlx *mlx;
	
	mlx = (t_mlx*)param;
	if (keycode == 53)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		exit(0);
	}
	return (1);
}

int closes(void *param)
{
	t_mlx *mlx;
	
	mlx = (t_mlx*)param;
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	exit(0);
	return (0);
}

int	strslen(char **strs)
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

int	**read_file(char *filename, t_mlx *mlx)
{
	int fd;
	char *line;
	char **strs;
	int	**ret = NULL;
	int **tmp = NULL;
	int *row;
	int i;
	int j;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error opening file\n");
		exit(-1);
	}
	i = 1;
	while (get_next_line(fd, &line) != 0)
	{
		tmp = ret;
		strs = ft_strsplit(line, ' ');
		if (mlx->x_len != 0)
		{
			if (mlx->x_len != strslen(strs))
			{
				ft_printf("Error in map\n");
				exit(-1);
			}
		}
		else
			mlx->x_len = strslen(strs);
		ret = (int **)malloc(sizeof(int*) * i);
		row = (int *)malloc(sizeof(int) * mlx->x_len);
		j = -1;
		while (++j < mlx->x_len)
		{
			row[j] = ft_atoi(strs[j]);
			if (mlx->z_len < row[j])
				mlx->z_len = row[j];
		}
		if (tmp != NULL)
		{
			j = -1;
			while (++j < i - 1)
				ret[j] = tmp[j];
			ret[j] = row;
			free(tmp);
		}
		else
			ret[0] = row;
		i++;
		free(line);
	}
	close(fd);
	mlx->y_len = i - 1;
	return (ret);
}

unsigned int set_color(t_mlx *mlx, double p1[3], double p2[3])
{
	(void)p1;
	(void)p2;
	return (mlx_get_color_value(mlx->mlx_ptr, 0x00FFFF));
}

void	update_img(t_mlx *mlx, int x, int y)
{
	int j;

	j = 0;
	while (j < mlx->bpp / 8)
	{
		*(mlx->address + (mlx->sl * y + mlx->bpp * x / 8 + j)) = (mlx->color >> (8 * j)) & 0xFF;
		j++;
	}
}

void	plotlow(t_mlx *mlx, int p1[2], int p2[2])
{
	int dx;
	int dy;
	int yi;
	int D;
	int y;

	dx = p2[0] - p1[0];
	dy = p2[1] - p1[1];
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	D = 2 * dy - dx;
	y = p1[1];
	while (p1[0] < p2[0])
	{
		update_img(mlx, p1[0], y);
		if (D > 0)
		{
			y = y + yi;
			D = D - 2 * dx;
		}
		D = D + 2 * dy;
		p1[0]++;
	}
}

void	plothigh(t_mlx *mlx, int p1[2], int p2[2])
{
	int dx;
	int dy;
	int xi;
	int D;
	int x;

	dx = p2[0] - p1[0];
	dy = p2[1] - p1[1];
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	D = 2 * dx - dy;
	x = p1[0];
	while (p1[1] < p2[1])
	{
		update_img(mlx, x, p1[1]);
		if (D > 0)
		{
			x = x + xi;
			D = D - 2 * dy;
		}
		D = D + 2 * dx;
		p1[1]++;
	}
}

double calc(int cam[2], int p1[3])
{
	double ret;

	ret = sqrt(pow((cam[0] - p1[0]), 2) + pow((cam[1] - p1[1]), 2));
	return (ret);
}

void	hypo_to_coord(int **pt, double hypo, double angle)
{
	double adj;
	double ops;

	adj = cos(angle) * hypo;
	ops = sin(angle) * hypo;
	(*pt)[0] = (int)round(ops);
	(*pt)[1] = (int)round(adj);
}

double		*projection(t_mlx *mlx, double p1[3], double p2[3])
{
	double *pt;
	double hypo;
	double angle;
	double length;
	double theta;
	double phi;
	double factor;

	theta = M_PI_2;
	phi = 0;
	pt = (double *)malloc(sizeof(double) * 4);
	p1[0] = .5 + (p1[0] - .5) * cos(phi) - (.5 - p1[1]) * sin(phi);
	p1[1] = .5 - (.5 - p1[1]) * cos(phi) + (.5 - p1[0]) * sin(phi);
	p2[0] = .5 + (p2[0] - .5) * cos(phi) - (.5 - p2[1]) * sin(phi);
	p2[1] = .5 - (.5 - p2[1]) * cos(phi) + (.5 - p2[0]) * sin(phi);
	pt[0] = F_LEN * (p1[0] - .5) / (CAM_DIST + (.5 - p1[1]) * sin(theta)) + .5;
	pt[1] = .5 - ((F_LEN * (((.5 - p1[1])) * cos(theta) + (sin(theta) * (p1[2]))) / (CAM_DIST + (.5 - p1[1]) * sin(theta))));
	pt[2] = F_LEN * (p2[0] - .5)  / (CAM_DIST + (.5 - p2[1]) * sin(theta)) + .5;
	pt[3] = .5 - ((F_LEN * (((.5 - p2[1])) * cos(theta) + (sin(theta) * (p2[2]))) / (CAM_DIST + (.5 - p2[1]) * sin(theta))));
//printf("%f: %f, %f %f\n", pt[0], pt[1], pt[2], pt[3]);
	return (pt);
}

void	draw_line(t_mlx *mlx, double d_p1[3], double d_p2[3])
{
	t_color color;
	double *pt;
	int p1[2];
	int p2[2];

	mlx->color = set_color(mlx, d_p1, d_p2);
	pt = projection(mlx, d_p1, d_p2);
	p1[0] = round(pt[0] * WIND_X);
	p1[1] = round(pt[1] * WIND_Y);
	p2[0] = round(pt[2] * WIND_X);
	p2[1] = round(pt[3] * WIND_Y);

	if (p1[0] > WIND_X || p1[0] < 0)
		p1[0] = WIND_X - 1;
	if (p2[0] > WIND_X || p2[0] < 0)
		p2[0] = WIND_X - 1;
	if (p1[1] > WIND_Y || p1[1] < 0)
		p1[1] = WIND_Y - 1;
	if (p2[1] > WIND_Y || p2[1] < 0)
		p2[1] = WIND_Y - 1;
//ft_printf("%i: %i, %i %i\n", p1[0], p1[1], p2[0], p2[1]);
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

void	draw_update(t_mlx *mlx, int **data)
{
	int bpp;
	int red;
	int size_line;
	int endian;
	int x;
	int y;
	double p1[3];
	double p2[3];

	mlx->image = mlx_new_image(mlx->mlx_ptr, WIND_X, WIND_Y);
	mlx->address = mlx_get_data_addr(mlx->image, &bpp, &size_line, &endian);
	mlx->bpp = bpp;
	mlx->sl = size_line;
	y = 0;
	while (y < mlx->y_len)
	{
		x = 0;
		while (x + 1 < mlx->x_len)
		{
//protec these later
			p1[0] = (double)x / mlx->x_len;
			p1[1] = (double)y / mlx->y_len;
			p1[2] = (double)data[y][x] / mlx->z_len;
			p2[0] = (double)(x + 1) / mlx->x_len;
			p2[1] = (double)y / mlx->y_len;
			p2[2] = (double)data[y][x + 1] / mlx->z_len;
//printf("POINTS: %f: %f, %f %f\n", p1[0], p1[1], p2[0], p2[1]);
			draw_line(mlx, p1, p2);
			x++;
		}
		y++;
	}
	x = 0;
	while (x < mlx->x_len)
	{
		y = 0;
		while (y + 1 < mlx->y_len)
		{
			p1[0] = (double)x / mlx->x_len;
			p1[1] = (double)y / mlx->y_len;
			p1[2] = (double)data[y][x] / mlx->z_len;
			p2[0] = (double)x / mlx->x_len;
			p2[1] = (double)(y + 1) / mlx->y_len;
			p2[2] = (double)data[y + 1][x] / mlx->z_len;
			draw_line(mlx, p1, p2);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->image, 0, 0);
}

void	build(t_mlx *mlx, int **data)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIND_X, WIND_Y, "mlx test");
	draw_update(mlx, data);
	mlx_hook(mlx->win_ptr, 2, 0, key_press, (void*)mlx);
	mlx_hook(mlx->win_ptr, 17, 0, closes, (void*)mlx);
	mlx_loop(mlx->mlx_ptr);
}

int main (int argc, char **argv)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_mlx	*mlx;
	int		**data;


	if (argc == 2)
	{
		mlx = (t_mlx*)malloc(sizeof(t_mlx));
		mlx->y_len = 0;
		mlx->x_len = 0;
		mlx->z_len = 0;
		data = read_file(argv[1], mlx);
		build(mlx, data);
	}
		return (0);
}
