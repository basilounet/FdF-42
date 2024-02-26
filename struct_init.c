/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:49:13 by bvasseur          #+#    #+#             */
/*   Updated: 2024/01/29 22:43:14 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/fdf.h"

void	fdf_init(t_fdf *fdf)
{
	fdf->mlx = 0;
	fdf->map = NULL;
	fdf->height = 0;
	fdf->width = 0;
	fdf->split_map = NULL;
	fdf->points = NULL;
	fdf->scale = 16;
	fdf->z_scale = 8;
}
