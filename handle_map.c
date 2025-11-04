/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajesus- <dajesus-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:32:45 by dajesus-          #+#    #+#             */
/*   Updated: 2025/01/10 11:15:31 by dajesus-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fill_matrix_with_color(int *z_line, int *color_line, char *line,
		int max_colums)
{
	int		i;
	char	**nums;
	char	**parts;

	nums = ft_split(line, ' ');
	i = 0;
	while (nums[i] && i < max_colums)
	{
		parts = ft_split(nums[i], ',');
		z_line[i] = ft_atoi(parts[0]);
		if (parts[1])
			color_line[i] = parse_hex_color(parts[1]);
		else
			color_line[i] = 0xFFFFFF;
		free(parts[0]);
		if (parts[1])
			free(parts[1]);
		free(parts);
		free(nums[i]);
		i++;
	}
	while (nums[i])
		free(nums[i++]);
	free(nums);
}

static int	allocate_z_matrix(t_fdf *data)
{
	int	i;

	data->z_matrix = (int **)malloc(data->height * sizeof(int *));
	if (!data->z_matrix)
		return (-1);
	i = 0;
	while (i < data->height)
	{
		data->z_matrix[i] = (int *)malloc(data->width * sizeof(int));
		if (!data->z_matrix[i])
		{
			free_int_array(data->z_matrix, i);
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	allocate_color_matrix(t_fdf *data)
{
	int	i;

	data->color_matrix = (int **)malloc(data->height * sizeof(int *));
	if (!data->color_matrix)
		return (-1);
	i = 0;
	while (i < data->height)
	{
		data->color_matrix[i] = (int *)malloc(data->width * sizeof(int));
		if (!data->color_matrix[i])
		{
			free_int_array(data->color_matrix, i);
			return (-1);
		}
		i++;
	}
	return (0);
}

void	fill_z_and_color_matrix(char *file_name, t_fdf *data)
{
	int		i;
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY, 0);
	if (fd < 0)
		return ;
	if (allocate_z_matrix(data) == -1 || allocate_color_matrix(data) == -1)
	{
		close(fd);
		exit(1);
	}
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		fill_matrix_with_color(data->z_matrix[i], data->color_matrix[i], line,
			data->width);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
}
