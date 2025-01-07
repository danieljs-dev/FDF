/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajesus- <dajesus-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:11:10 by dajesus-          #+#    #+#             */
/*   Updated: 2025/01/06 21:15:51 by dajesus-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define WINDOW_CLOSE	17
#define KEY_ESC			65307

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
//	mlx_destroy_image(data->mlx_ptr, data->img_data);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free_int_array(data->z_matrix, data->height);
	data->z_matrix = NULL;
	free(data->mlx_ptr);
	free(data);
	exit(0);
}

int	mouse_hook(int button, int x, int y, t_fdf *data)
{
	(void)x;
	(void)y;
	if (button == 4) // Scroll para cima
	{
		data->zoom += 1;
		if (data->zoom > 50) // Limite máximo de zoom
			data->zoom = 50;
	}
	else if (button == 5) // Scroll para baixo
	{
		data->zoom -= 1;
		if (data->zoom < 1) // Limite mínimo de zoom
			data->zoom = 1;
	}
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	draw(data);
	return (0);
}

int	deal_key(int key, t_fdf *data)
{
	if (key == 61 || key == 65451) // '+' (teclado principal ou numérico)
		data->z_scale += 0.5;
	if (key == 45 || key == 65453) // '-' (teclado principal ou numérico)
		data->z_scale -= 0.5;
	if (data->z_scale < 0.1)
		data->z_scale = 0.1;
	if (key == 65362)
		data->shift_y -= 50;
	if (key == 65364)
		data->shift_y += 50;
	if (key == 65361)
		data->shift_x -= 50;
	if (key == 65363)
		data->shift_x += 50;
	if (key == KEY_ESC || key == WINDOW_CLOSE)
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
	data->z_scale = 1.0;
	draw(data);
	mlx_hook(data->win_ptr, WINDOW_CLOSE, 0, cleanup, data);
	mlx_key_hook(data->win_ptr, &deal_key, data);
	mlx_hook(data->win_ptr, 4, 1L << 2, mouse_hook, data); // Evento do mouse
	mlx_hook(data->win_ptr, 5, 1L << 3, mouse_hook, data); // Evento do mouse
	mlx_loop(data-> mlx_ptr);
	cleanup(data);
	return (0);
}
