/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 18:30:51 by tdiaz             #+#    #+#             */
/*   Updated: 2019/03/12 18:30:53 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** These functions will parse a well formated .fdf files. Some of the maps
** contain color information but I have chosen to ignore that aspect and place
** my own color.
*/

#include "wire.h"

static void	set_check_x_len(t_mlx *mlx, char **strs)
{
	int slen;

	slen = strslen(strs);
	if (mlx->x_len != 0)
	{
		if (mlx->x_len != slen || slen == 0)
		{
			ft_printf("Error in map\n");
			exit(-1);
		}
	}
	else
		mlx->x_len = slen;
}

static void	set_copy_vals(t_mlx *mlx, char **strs, int *row)
{
	int j;

	j = 0;
	while (j < mlx->x_len)
	{
		row[j] = ft_atoi(strs[j]);
		if (mlx->z_len < row[j])
			mlx->z_len = row[j];
		j += 1;
	}
}

static void	copy_free_vals(int **ret, int *row, int **tmp, int i)
{
	int j;

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
}

void		read_file(int fd, t_mlx *mlx, int i)
{
	char	*line;
	char	**strs;
	int		**ret;
	int		**tmp;
	int		*row;

	error_in_read(fd);
	ret = NULL;
	tmp = NULL;
	while (get_next_line(fd, &line) != 0)
	{
		tmp = ret;
		strs = ft_strsplit(line, ' ');
		set_check_x_len(mlx, strs);
		init_data(&ret, &row, i, mlx);
		set_copy_vals(mlx, strs, row);
		copy_free_vals(ret, row, tmp, i);
		free(line);
		freestrs(&strs);
		i++;
	}
	close_and_free(line, fd);
	mlx->y_len = i - 1;
	mlx->data = ret;
}
