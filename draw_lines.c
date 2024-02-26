/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:01:59 by bvasseur          #+#    #+#             */
/*   Updated: 2024/01/30 15:54:51 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/fdf.h"

static void	print_pixel(t_fdf *fdf, size_t x_tmp, size_t y_tmp, int color)
{
	if ((0 <= x_tmp && x_tmp <= WIDTH) && (0 <= y_tmp && y_tmp <= HEIGHT))
		mlx_put_pixel(fdf->img, x_tmp, y_tmp, color);
}

static void	x_cartesian_equation(t_fdf *fdf, t_ce ce, t_point pos1, t_point pos2)
{
	t_point	tmp;

	if (pos1.x > pos2.x)
	{
		tmp = pos2;
		pos2 = pos1;
		pos1 = tmp;
	}
	ce.c = -ce.dy * pos1.x + ce.dx * pos1.y;
	ce.x = pos1.x;
	while (ce.x <= pos2.x)
	{
		ce.y = (-ce.dy * ce.x - ce.c) / -ce.dx;
		print_pixel(fdf, ce.x, ce.y, pos2.color);
		ce.x++;
	}
}

static void	y_cartesian_equation(t_fdf *fdf, t_ce ce, t_point pos1, t_point pos2)
{
	t_point	tmp;

	if (pos1.y > pos2.y)
	{
		tmp = pos2;
		pos2 = pos1;
		pos1 = tmp;
	}
	ce.c = -ce.dy * pos1.x + ce.dx * pos1.y;
	ce.y = pos1.y;
	while (ce.y <= pos2.y)
	{
		ce.x = (ce.dx * ce.y - ce.c) / ce.dy;
		print_pixel(fdf, ce.x, ce.y, pos2.color);
		ce.y++;
	}
}

void	print_line(t_fdf *fdf, t_point pos1, t_point pos2)
{
	t_ce	ce;

	ce.dx = pos1.x - pos2.x;
	ce.dy = pos1.y - pos2.y;
	if (ce.dx == 0 && ce.dy == 0)
		return ;
	if (ft_abs(ce.dx) > ft_abs(ce.dy))
		x_cartesian_equation(fdf, ce, pos1, pos2);
	else
		y_cartesian_equation(fdf, ce, pos1, pos2);
}
