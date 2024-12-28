/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajesus- <dajesus-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 08:50:27 by dajesus-          #+#    #+#             */
/*   Updated: 2024/12/28 09:04:14 by dajesus-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	bresenham_steps(t_bresenham_params *params)
{
	float	max_step;

	params->x_step = params->x1 - params->x;
	params->y_step = params->y1 - params->y;
	max_step = max(absolute(params->x_step), absolute(params->y_step));
	params->x_step /= max_step;
	params->y_step /= max_step;
}

static void	bresenham_draw(t_bresenham_params *params, t_fdf *data)
{
	while ((int)(params->x - params->x1) || (int)(params->y - params->y1))
	{
		put_pixel_to_image(data, params->x, params->y, data->color);
		params->x += params->x_step;
		params->y += params->y_step;
	}
}

void	isometric(float *x, float *y, int z)
{
	static float	cos_angle;
	static float	sin_angle;

	cos_angle = 0.8;
	sin_angle = 0.8;
	*x = (*x - *y) * cos(cos_angle);
	*y = (*x + *y) * sin(sin_angle) - z;
}

void	bresenham(t_bresenham_params *params, t_fdf *data)
{
	int		z;
	int		z1;

	z = 0;
	z1 = 0;
	z = data->z_matrix[(int)params->y][(int)params->x];
	z1 = data->z_matrix[(int)params->y1][(int)params->x1];
	params->x *= data->zoom;
	params->y *= data->zoom;
	params->x1 *= data->zoom;
	params->y1 *= data->zoom;
	if (z || z1)
		data->color = 0xe80c0c;
	else
		data->color = 0x0492c2;
	isometric(&params->x, & params->y, z);
	isometric(&params->x1, & params->y1, z1);
	params->x += data->shift_x;
	params->y += data->shift_y;
	params->x1 += data->shift_x;
	params->y1 += data->shift_y;
	bresenham_steps(params);
	bresenham_draw(params, data);
}
