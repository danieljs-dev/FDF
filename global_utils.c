/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajesus- <dajesus-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 08:48:30 by dajesus-          #+#    #+#             */
/*   Updated: 2025/01/06 18:18:28 by dajesus-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

float	absolute(float a)
{
	if (a < 0)
		return (-a);
	return (a);
}

void	put_pixel_to_image(t_fdf *data, int x, int y, int color)
{
	if (x >= 0 && x < 1024 && y >= 0 && y < 768)
		data->img_data[y * 1024 + x] = color;
}

void	create_image(t_fdf *data)
{
	data->img_ptr = mlx_new_image(data->mlx_ptr, 1024, 768);
	data->img_data = (int *)mlx_get_data_addr(data->img_ptr, &data->bpp,
			&data->size_line, &data->endian);
}

int	ft_wdcounter(char const *str, char c)
{
	int		i;
	int		words;

	words = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i])
			words++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (words);
}
