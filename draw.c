/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajesus- <dajesus-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 00:29:52 by dajesus-          #+#    #+#             */
/*   Updated: 2025/01/06 18:18:25 by dajesus-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_horizontal_lines(t_fdf *data, t_bresenham_params *params)
{
	int		x;
	int		y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width - 1)
		{
			params->x = x;
			params->y = y;
			params->x1 = x + 1;
			params->y1 = y;
			bresenham(params, data);
			x++;
		}
		y++;
	}
}

static void	draw_vertical_lines(t_fdf *data, t_bresenham_params *params)
{
	int		x;
	int		y;

	y = 0;
	while (y < data->height - 1)
	{
		x = 0;
		while (x < data->width)
		{
			params->x = x;
			params->y = y;
			params->x1 = x;
			params->y1 = y + 1;
			bresenham(params, data);
			x++;
		}
		y++;
	}
}

void	draw(t_fdf *data)
{
	t_bresenham_params	params;

	create_image(data);
	draw_horizontal_lines(data, &params);
	draw_vertical_lines(data, &params);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	mlx_destroy_image(data->mlx_ptr, data->img_ptr);
}
