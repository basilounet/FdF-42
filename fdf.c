/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:36:46 by bvasseur          #+#    #+#             */
/*   Updated: 2024/02/12 21:21:43 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/fdf.h"
#include <math.h>

t_point	iso_pos(t_fdf *fdf, t_point pos, int x_origin)
{
	t_point	newpos;

	newpos.x = ((pos.x - pos.y) * fdf->scale + x_origin) * cos(0.523599);
    newpos.y = ((pos.x + pos.y) * fdf->scale + x_origin) * sin (0.523599) - pos.z * fdf->z_scale;
	newpos.color = pos.color;
	return (newpos);
}

void	print_fdf(t_fdf *fdf)
{
	size_t	x;
	size_t	y;
	t_point	pos1;
	t_point	pos2;

	y = 0;
	while (y < fdf->height - 1)
	{
		x = 0;
		while (x < fdf->width - 1)
		{
			pos1 = iso_pos(fdf, fdf->points[y][x], WIDTH / 2);
			pos2 = iso_pos(fdf, fdf->points[y][x + 1], WIDTH / 2);
			print_line(fdf, pos1, pos2);
			pos1 = iso_pos(fdf, fdf->points[y][x], WIDTH / 2);
			pos2 = iso_pos(fdf, fdf->points[y + 1][x], WIDTH / 2);
			print_line(fdf, pos1, pos2);
			x++;
		}
		y++;
	}
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		unleak(fdf);
		exit(0);
	}
	if (keydata.key == MLX_KEY_DOWN)
		fdf->z_scale -= 1;
	if (keydata.key == MLX_KEY_UP)
		fdf->z_scale += 1;
	if (keydata.key == MLX_KEY_LEFT)
		fdf->scale -= 1;
	if (keydata.key == MLX_KEY_RIGHT)
		fdf->scale += 1;
	//ft_printf("%d\n", fdf->z_scale);
	mlx_delete_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(fdf->mlx, fdf->img, 0, 0);
	print_fdf(fdf);
}


void	window_initiate(t_fdf *fdf)
{
	fdf->mlx = mlx_init(WIDTH, HEIGHT, "FdF", false);
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->mlx || !fdf->img)
		error(fdf, MLX_ERROR);
	mlx_image_to_window(fdf->mlx, fdf->img, 0, 0);
}

void	update(void *param)
{
	t_fdf	*fdf;
	static	int	frame = 0;

	fdf = (t_fdf *)param;
	frame++;
	if (frame % 50 == 0)
	{
		fdf->z_scale = ft_rand(-2, 2);
		mlx_delete_image(fdf->mlx, fdf->img);
		fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
		mlx_image_to_window(fdf->mlx, fdf->img, 0, 0);
		print_fdf(fdf);
	}
}

int	main(int ac, char **av)
{
	t_fdf	fdf;

	map_analyser(ac, av, &fdf);
	window_initiate(&fdf);
	print_fdf(&fdf);
	mlx_key_hook(fdf.mlx, &my_keyhook, &fdf);
	//mlx_loop_hook(fdf.mlx, &update, &fdf);
	mlx_loop(fdf.mlx);
	unleak(&fdf);
	exit(0);
}
