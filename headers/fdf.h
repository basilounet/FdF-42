/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:35:50 by bvasseur          #+#    #+#             */
/*   Updated: 2024/01/29 23:12:19 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# define WIDTH 1500
# define HEIGHT 900
# define DEFAULT_COLOR 0xffffffff

enum				e_errors
{
	INVALID_FD = 1,
	INVALID_FORMAT = 2,
	EMPTY_MAP = 3,
	INVALID_CHARACTER = 4,
	INVALID_SHAPE = 5,
	MALLOC_ERROR = 6,
	INVALID_AC_AMOUNT = 7,
	MISSING_FORMAT = 8,
	MLX_ERROR = 9
};

typedef struct s_cartesian_equation
{
	int				dx;
	int				dy;
	int				c;
	int				x;
	int				y;
}					t_ce;

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	unsigned int	color;
}					t_point;

typedef struct s_fdf
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	char			**map;
	char			***split_map;
	t_point			**points;
	size_t			height;
	size_t			width;
	int				scale;
	int				z_scale;
}					t_fdf;

/*======== MAP_ANALYSER ========*/

void				map_analyser(int ac, char **av, t_fdf *fdf);

/*========  ERRORS ========*/

void				error(t_fdf *fdf, enum e_errors name);

/*======== UNLEAK ========*/

void				unleak(t_fdf *fdf);
void				free_gnl(int fd, t_fdf *fdf, char *str);

/*======== STRUCT_INIT ========*/

void				fdf_init(t_fdf *fdf);

/*======== STRUCT_INIT ========*/

void				print_line(t_fdf *fdf, t_point pos1, t_point pos2);

#endif
