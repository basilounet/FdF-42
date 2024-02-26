/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:08:48 by bvasseur          #+#    #+#             */
/*   Updated: 2024/01/23 18:01:37 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/fdf.h"

void	error(t_fdf *fdf, enum e_errors name)
{
	unleak(fdf);
	write(1, "Error\n", 6);
	if (name == INVALID_FD)
		write(1, "[ ! ERROR ! ] File not found\n", 29);
	else if (name == INVALID_FORMAT)
		write(1, "[ ! ERROR ! ] The format is not .fdf\n", 37);
	else if (name == EMPTY_MAP)
		write(1, "[ ! ERROR ! ] The file is empty\n", 32);
	else if (name == INVALID_CHARACTER)
		write(1, "[ ! ERROR ! ] There is an invalid character\n", 44);
	else if (name == INVALID_SHAPE)
		write(1, "[ ! ERROR ! ] The map must be a rectangle\n", 42);
	else if (name == MALLOC_ERROR)
		write(1, "[ ! ERROR ! ] A malloc error occured\n", 37);
	else if (name == INVALID_AC_AMOUNT)
		write(1, "[ ! ERROR ! ] Incorrect numbers of arguments\n", 45);
	else if (name == MISSING_FORMAT)
		write(1, "[ ! ERROR ! ] There is no format\n", 33);
	else if (name == MLX_ERROR)
		write(1, "[ ! ERROR ! ] Mlx malloc error\n", 31);
	exit(name);
}
