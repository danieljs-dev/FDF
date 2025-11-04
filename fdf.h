/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajesus- <dajesus-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:11:13 by dajesus-          #+#    #+#             */
/*   Updated: 2025/01/10 11:32:09 by dajesus-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "keys.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include "MLX42/MLX42.h"

# define WIN_W 1024
# define WIN_H 768
# define MIN_ZOOM 1
# define MAX_ZOOM 50

typedef struct s_fdf
{
	int				zoom;
	int				color;
	int				width;
	int				height;
	int				shift_x;
	int				shift_y;
	float			z_scale;

	// MLX42 handles
	mlx_t			*mlx;
	mlx_image_t		*img;

	int				**z_matrix;
	int				**color_matrix;
}					t_fdf;

typedef struct s_bresenham_params
{
	float	x;
	float	y;
	float	x1;
	float	y1;
	float	x_step;
	float	y_step;
}            t_bresenham_params;

int			cleanup(t_fdf *data);
int			open_file(char *file_name);
int			parse_hex_color(const char *hex);

void		draw(t_fdf *data);
void		create_image(t_fdf *data);
void		free_int_array(int **array, int height);
void		read_file(char *file_name, t_fdf *data);
void		validate_file_extension(char *file_name);
void		validate_line(char *line, t_fdf *data, int fd);
void		bresenham(t_bresenham_params *params, t_fdf *data);
// void		isometric(float *x, float *y, int z, float z_scale);
void		fill_z_and_color_matrix(char *file_name, t_fdf *data);
void		put_pixel_to_image(t_fdf *data, int x, int y, int color);
void		cleanup_and_exit(t_fdf *data, int fd, char *line, int code);

#endif
