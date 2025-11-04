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
	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
		data->img_data[y * WIN_W + x] = color;
}

void	create_image(t_fdf *data)
{
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	if (!data->img_ptr)
		exit(1);
	data->img_data = (int *)mlx_get_data_addr(data->img_ptr, &data->bpp,
			&data->size_line, &data->endian);
	if (!data->img_data)
		exit(1);
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
