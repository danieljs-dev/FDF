/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajesus- <dajesus-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:11:13 by dajesus-          #+#    #+#             */
/*   Updated: 2024/12/19 12:00:30 by dajesus-         ###   ########.fr       */
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

	int		key_up;
	int		key_down;
	int		key_left;
	int		key_right;

	int		**z_matrix;
	void	*mlx_ptr;
	void	*win_ptr;
}			t_fdf;

void	draw(t_fdf *data);
void	read_file(char *file_name, t_fdf *data);
void	bresenham(float x, float y, float x1, float y1, t_fdf *data);

#endif
