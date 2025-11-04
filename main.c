/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajesus- <dajesus-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:11:10 by dajesus-          #+#    #+#             */
/*   Updated: 2025/01/10 11:29:51 by dajesus-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	cleanup(t_fdf *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free_int_array(data->z_matrix, data->height);
	free_int_array(data->color_matrix, data->height);
	data->z_matrix = NULL;
	free(data->mlx_ptr);
	free(data);
	exit(0);
}

int	mouse_hook(int button, int x, int y, t_fdf *data)
{
	(void)x;
	(void)y;
	if (button == SCROLL_UP)
	{
		data->zoom += 1;
		if (data->zoom > MAX_ZOOM)
			data->zoom = MAX_ZOOM;
	}
	else if (button == SCROLL_DOWN)
	{
		data->zoom -= 1;
		if (data->zoom < MIN_ZOOM)
			data->zoom = MIN_ZOOM;
	}
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	draw(data);
	return (0);
}

int	deal_key(int key, t_fdf *data)
{
	if (key == KEY_UP)
		data->shift_y -= 50;
	if (key == KEY_DOWN)
		data->shift_y += 50;
	if (key == KEY_LEFT)
		data->shift_x -= 50;
	if (key == KEY_RIGHT)
		data->shift_x += 50;
	if (key == KEY_PLUS || key == KEY_PLUS_NUMPAD)
		data->z_scale += 0.5;
	if (key == KEY_MINUS || key == KEY_MINUS_NUMPAD)
		data->z_scale -= 0.5;
	if (data->z_scale < 0.1)
		data->z_scale = 0.1;
	if (key == KEY_ESC || key == WINDOW_CLOSE)
		return (cleanup(data));
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
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
	int		fd;

	if (argc != 2)
		return (1);
	fd = open_file(argv[1]);
	close(fd);
	data = (t_fdf *)malloc(sizeof(t_fdf));
	if (!data)
		return (1);
	read_file(argv[1], data);
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_W, WIN_H, "FDF");
	calculate_zoom(data, WIN_W, WIN_H);
	data->shift_x = (WIN_W - (data->width * data->zoom)) / 2;
	data->shift_y = (WIN_H - (data->height * data->zoom)) / 2;
	data->z_scale = 1.0;
	draw(data);
	mlx_hook(data->win_ptr, WINDOW_CLOSE, 0, cleanup, data);
	mlx_key_hook(data->win_ptr, &deal_key, data);
	mlx_hook(data->win_ptr, 4, 1L << 2, mouse_hook, data);
	mlx_hook(data->win_ptr, 5, 1L << 3, mouse_hook, data);
	mlx_loop(data->mlx_ptr);
	cleanup(data);
	return (0);
}
