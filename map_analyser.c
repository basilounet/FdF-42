/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_analyser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:38:48 by bvasseur          #+#    #+#             */
/*   Updated: 2024/01/30 14:33:54 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/fdf.h"
#include <math.h>

void	get_point(t_fdf *fdf, size_t x, size_t y)
{
	unsigned int	color;
	int				i;

	color = DEFAULT_COLOR;
	fdf->points[y][x].x = x;
	fdf->points[y][x].y = y;
	fdf->points[y][x].z = ft_atoi(fdf->split_map[y][x]);
	if (ft_strchr(fdf->split_map[y][x], 'x'))
	{
		i = -1;
		while (fdf->split_map[y][x][++i])
			fdf->split_map[y][x][i] = ft_tolower(fdf->split_map[y][x][i]);
		color = ft_btoi(ft_strchr(fdf->split_map[y][x], 'x') + 1,
				"0123456789abcdef");
		color = (color << 8) | 0xff;
	}
	fdf->points[y][x].color = color;
}

static void	take_points_data(t_fdf *fdf)
{
	size_t	x;
	size_t	y;

	y = 0;
	fdf->points = ft_calloc(sizeof(t_point *), fdf->height + 1);
	if (!fdf->points)
		error(fdf, MALLOC_ERROR);
	while (y < fdf->height)
	{
		x = 0;
		fdf->points[y] = ft_calloc(sizeof(t_point), fdf->width + 1);
		if (!fdf->points[y])
			error(fdf, MALLOC_ERROR);
		while (x < fdf->width)
			get_point(fdf, x++, y);
		y++;
	}
}

static int	is_point_correct(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if ((str[i] == '+' || str[i] == '-') && str[i + 1] != 0)
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] && ft_strncmp(&str[i], ",0x", 3) == 0)
		i += 3;
	else
		return (str[i] == 0);
	while (str[i] && (ft_isdigit(str[i]) || ('A' <= str[i] && str[i] <= 'F')
			|| ('a' <= str[i] && str[i] <= 'f')))
		i++;
	return (str[i] == 0);
}

static void	check_all_points(t_fdf *fdf)
{
	char	***split_map;
	int		i;
	int		j;

	split_map = fdf->split_map;
	i = 0;
	while (split_map[i])
	{
		j = 0;
		while (split_map[i][j])
			if (!is_point_correct(split_map[i][j++]))
				error(fdf, INVALID_CHARACTER);
		if (ft_maplen(split_map[i]) != fdf->width)
			error(fdf, INVALID_SHAPE);
		i++;
	}
}

void	map_analyser(int ac, char **av, t_fdf *fdf)
{
	int	fd;

	fdf_init(fdf);
	if (ac != 2)
		error(fdf, INVALID_AC_AMOUNT);
	if (ft_strrchr(av[1], '.') == NULL)
		error(fdf, MISSING_FORMAT);
	if (ft_strncmp(ft_strrchr(av[1], '.'), ".fdf", 5) != 0)
		error(fdf, INVALID_FORMAT);
	fd = open(av[1], O_RDONLY);
	close(fd);
	if (fd < 0)
		error(fdf, INVALID_FD);
	fdf->map = ft_get_map_fd(av[1]);
	fdf->split_map = ft_get_split_map(fdf->map, ' ');
	if (!fdf->map || !fdf->split_map)
		error(fdf, MALLOC_ERROR);
	fdf->height = ft_numbers_of_lines(av[1]);
	fdf->width = ft_maplen(fdf->split_map[0]);
	check_all_points(fdf);
	take_points_data(fdf);
	fdf->scale = ft_min(WIDTH / fdf->width, HEIGHT / fdf->height) - 4;
}
