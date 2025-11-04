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

static void	on_close(void *param)
{
	t_fdf *data = (t_fdf *)param;
	(void)data;
	// Signal window to close; actual cleanup happens after loop returns
	if (data && data->mlx)
		mlx_close_window(data->mlx);
}

static void	on_scroll(double xdelta, double ydelta, void *param)
{
	t_fdf *data;
	(void)xdelta;
	data = (t_fdf *)param;
	if (!data)
		return ;
	if (ydelta > 0)
	{
		data->zoom += 1;
		if (data->zoom > MAX_ZOOM)
			data->zoom = MAX_ZOOM;
	}
	else if (ydelta < 0)
	{
		data->zoom -= 1;
		if (data->zoom < MIN_ZOOM)
			data->zoom = MIN_ZOOM;
	}
	draw(data);
}

static void	on_key(mlx_key_data_t keydata, void *param)
{
	t_fdf *data = (t_fdf *)param;
	if (!data)
		return ;

	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_UP)
			data->shift_y -= 50;
		if (keydata.key == MLX_KEY_DOWN)
			data->shift_y += 50;
		if (keydata.key == MLX_KEY_LEFT)
			data->shift_x -= 50;
		if (keydata.key == MLX_KEY_RIGHT)
			data->shift_x += 50;
		if (keydata.key == MLX_KEY_EQUAL) // '+'
			data->z_scale += 0.05f;
		if (keydata.key == MLX_KEY_MINUS)
			data->z_scale -= 0.05f;
		if (data->z_scale < 0.1f)
			data->z_scale = 0.1f;
		if (keydata.key == MLX_KEY_ESCAPE)
		{
			mlx_close_window(data->mlx);
			return ;
		}
		draw(data);
	}
}

int	cleanup(t_fdf *data)
{
	if (!data)
		exit(0);
	if (data->img)
		mlx_delete_image(data->mlx, data->img);
	if (data->mlx)
		mlx_terminate(data->mlx);
	free_int_array(data->z_matrix, data->height);
	free_int_array(data->color_matrix, data->height);
	data->z_matrix = NULL;
	free(data);
	exit(0);
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
	data->mlx = mlx_init(WIN_W, WIN_H, "FDF", true);
	if (!data->mlx)
		return (1);
	calculate_zoom(data, WIN_W, WIN_H);
	data->shift_x = (WIN_W - (data->width * data->zoom)) / 2;
	data->shift_y = (WIN_H - (data->height * data->zoom)) / 2;
	data->z_scale = 1.0;
	data->img = NULL;
	create_image(data);
	draw(data);
	mlx_close_hook(data->mlx, &on_close, data);
	mlx_key_hook(data->mlx, &on_key, data);
	mlx_scroll_hook(data->mlx, &on_scroll, data);
	mlx_loop(data->mlx);
	cleanup(data);
	return (0);
}
