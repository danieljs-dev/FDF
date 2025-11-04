/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajesus- <dajesus-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 08:48:30 by dajesus-          #+#    #+#             */
/*   Updated: 2025/01/10 11:53:03 by dajesus-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel_to_image(t_fdf *data, int x, int y, int color)
{
	uint8_t *px;

	if (!data->img || !data->img->pixels)
		return ;
	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	px = &data->img->pixels[(y * WIN_W + x) * 4];
	px[0] = (color >> 16) & 0xFF; // R
	px[1] = (color >> 8) & 0xFF;  // G
	px[2] = (color) & 0xFF;       // B
	px[3] = 0xFF;                 // A
}

static void	clear_image(t_fdf *data)
{
	if (data->img && data->img->pixels)
		ft_bzero(data->img->pixels, WIN_W * WIN_H * 4);
}

void	create_image(t_fdf *data)
{
	if (!data->img)
	{
		data->img = mlx_new_image(data->mlx, WIN_W, WIN_H);
		if (!data->img)
			exit(1);
		if (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0)
			exit(1);
	}
	clear_image(data);
}

int	parse_hex_color(const char *hex)
{
	int	i;
	int	color;

	i = 0;
	color = 0;
	if (!hex || *hex == '\0')
		return (0xFFFFFF);
	if (*hex == '0' && (*(hex + 1) == 'x' || *(hex + 1) == 'X'))
		hex += 2;
	while (hex[i] && i < 6)
	{
		color *= 16;
		if (hex[i] >= '0' && hex[i] <= '9')
			color += hex[i] - '0';
		else if (hex[i] >= 'a' && hex[i] <= 'f')
			color += hex[i] - 'a' + 10;
		else if (hex[i] >= 'A' && hex[i] <= 'F')
			color += hex[i] - 'A' + 10;
		else
			break ;
		i++;
	}
	return (color);
}

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

int	open_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY, 0666);
	if (fd < 0)
		exit(1);
	return (fd);
}
