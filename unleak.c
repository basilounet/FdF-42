/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unleak.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:50:07 by bvasseur          #+#    #+#             */
/*   Updated: 2024/01/24 15:42:03 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/fdf.h"

void	free_gnl(int fd, t_fdf *fdf, char *str)
{
	while (str)
	{
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	error(fdf, MALLOC_ERROR);
}

void	free_points(t_fdf *fdf)
{
	size_t	i;

	if (!fdf->points)
		return ;
	i = 0;
	while (i < fdf->height)
		free(fdf->points[i++]);
	free(fdf->points);
}

void	unleak(t_fdf *fdf)
{
	ft_free_map(fdf->map, fdf->height);
	ft_free_split_map(fdf->split_map);
	free_points(fdf);
	if (!fdf->mlx)
		return ;
	mlx_close_window(fdf->mlx);
	mlx_terminate(fdf->mlx);
}
