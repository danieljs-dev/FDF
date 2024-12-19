/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajesus- <dajesus-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:11:10 by dajesus-          #+#    #+#             */
/*   Updated: 2024/12/19 12:35:57 by dajesus-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define WINDOW_CLOSE	17
#define KY_ESC			65307

void	free_int_array(int **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
			free(array[i++]);
		free(array);
	}
}

int	cleanup(t_fdf *data)
{
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->z_matrix)
		free_int_array(data->z_matrix);
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

int	main(int argc, char *argv[])
{
	t_fdf	*data;

	if (argc < 2)
		return (1);
	data = (t_fdf *)malloc(sizeof(t_fdf));
	read_file(argv[1], data);
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1000, 1000, "FDF");
	data->zoom = 20;
	//bresenham(10, 10, 600, 300, data);
	draw(data);
	mlx_key_hook(data->win_ptr, deal_key, data);
	mlx_loop(data-> mlx_ptr);
	free(data);
	return (0);
}

// https://youtu.be/10P59aOgi68?t=684
// FDF_caroldaniel
// FDF_erwkuvi

// valgrind --leak-check=full --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./fdf maps/test_maps/42.fdf