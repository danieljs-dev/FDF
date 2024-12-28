/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajesus- <dajesus-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:11:13 by dajesus-          #+#    #+#             */
/*   Updated: 2024/12/28 08:58:28 by dajesus-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft/libft.h"
//# include "MLX42/include/MLX42/MLX42.h"
# include "minilibx-linux/mlx.h"

typedef struct s_fdf
{
	int		zoom;
	int		color;
	int		width;
	int		height;
	int		shift_x;
	int		shift_y;

	int		bpp;
	int		size_line;
	int		endian;
	int		*img_data;
	void	*img_ptr;

	int		**z_matrix;
	void	*mlx_ptr;
	void	*win_ptr;
}			t_fdf;

typedef struct s_bresenham_params
{
	float	x;
	float	y;
	float	x1;
	float	y1;
	float	x_step;
	float	y_step;
}			t_bresenham_params;

void	draw(t_fdf *data);
void	free_int_array(int **array, int height);
void	read_file(char *file_name, t_fdf *data);
void	bresenham(t_bresenham_params *params, t_fdf *data);
int		cleanup(t_fdf *data);
void	create_image(t_fdf *data);
void	put_pixel_to_image(t_fdf *data, int x, int y, int color);
void	get_dimensions(char *file_name, t_fdf *data);
void	fill_z_matrix(char *file_name, t_fdf *data);
int		allocate_z_matrix(t_fdf *data);

float	max(float a, float b);
float	absolute(float a);
void	isometric(float *x, float *y, int z);

#endif
