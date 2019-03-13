/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 20:09:45 by tdiaz             #+#    #+#             */
/*   Updated: 2019/03/12 20:09:50 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Some boring functions that needed to be separated out because of 42 Silicon
** Valley's format rules. These functions are called in parse_map.c
*/

#include "wire.h"

void	error_in_read(int fd)
{
	if (fd < 0)
	{
		ft_printf("Error opening file\n");
		exit(-1);
	}
}

void	init_data(int ***ret, int **row, int i, t_mlx *mlx)
{
	*ret = (int **)malloc(sizeof(int*) * i);
	*row = (int *)malloc(sizeof(int) * mlx->x_len);
}

void	close_and_free(char *line, int fd)
{
	if (line)
		free(line);
	close(fd);
}
