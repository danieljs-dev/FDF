/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajesus- <dajesus-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:11:10 by dajesus-          #+#    #+#             */
/*   Updated: 2024/12/28 09:03:24 by dajesus-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define WINDOW_CLOSE	17
#define KY_ESC			65307

void	free_int_array(int **array, int height)
{
	int	i;

	i = 0;
	if (array)
	{
		while (i < height)
			free(array[i++]);
		free(array);
	}
}

int	cleanup(t_fdf *data)
{
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);
	if (data->z_matrix)
	{
		free_int_array(data->z_matrix, data->height);
		data->z_matrix = NULL;
	}
	free(data->mlx_ptr);
	free(data);
	exit(0);
}

int	deal_key(int key, t_fdf *data)
{
	ft_printf("%d\n", key);
	if (key == 65362)
		data->shift_y -= 10;
	if (key == 65364)
		data->shift_y += 10;
	if (key == 65361)
		data->shift_x -= 10;
	if (key == 65363)
		data->shift_x += 10;
	if (key == KY_ESC || key == WINDOW_CLOSE)
		return (cleanup(data));
	mlx_clear_window(data->mlx_ptr, data-> win_ptr);
	draw(data);
	return (0);
}

void	calculate_zoom(t_fdf *data, int win_w, int win_h)
{
	float	x_scale;
	float	y_scale;
	float	min_zoon;
	float	max_zoom;
	float	min_scale_percent;

	min_scale_percent = 0.8;
	x_scale = (win_w * min_scale_percent) / (data->width);
	y_scale = (win_h * min_scale_percent) / (data->height);
	if (x_scale < y_scale)
		data->zoom = x_scale;
	else
		data->zoom = y_scale;
	min_zoon = 1;
	max_zoom = 20;
	if (data->zoom < min_zoon)
		data->zoom = min_zoon;
	if (data->zoom > max_zoom)
		data->zoom = max_zoom;
}

int	main(int argc, char *argv[])
{
	t_fdf	*data;
	int		win_w;
	int		win_h;

	if (argc < 2)
		return (1);
	data = (t_fdf *)malloc(sizeof(t_fdf));
	if (!data)
		return (1);
	read_file(argv[1], data);
	win_w = 1024;
	win_h = 768;
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, win_w, win_h, "FDF");
	calculate_zoom(data, win_w, win_h);
	data->shift_x = (win_w - (data->width * data->zoom)) / 2;
	data->shift_y = (win_h - (data->height * data->zoom)) / 2;
	draw(data);
	mlx_key_hook(data->win_ptr, deal_key, data);
	mlx_loop(data-> mlx_ptr);
	cleanup(data);
	return (0);
}
