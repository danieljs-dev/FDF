/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajesus- <dajesus-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:11:16 by dajesus-          #+#    #+#             */
/*   Updated: 2024/12/28 09:06:04 by dajesus-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fill_matrix(int *z_line, char *line)
{
	int		i;
	char	**nums;

	nums = ft_split(line, ' ');
	i = 0;
	while (nums[i])
	{
		z_line[i] = ft_atoi(nums[i]);
		free(nums[i]);
		i++;
	}
	free(nums);
}

void	get_dimensions(char *file_name, t_fdf *data)
{
	int		fd;
	char	*line;
	int		lines_count;

	fd = open(file_name, O_RDONLY, 0);
	if (fd < 0)
		return ;
	lines_count = 0;
	line = get_next_line(fd);
	data->width = ft_wdcounter(line, ' ');
	while (line)
	{
		lines_count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	data->height = lines_count;
}

int	allocate_z_matrix(t_fdf *data)
{
	int		i;

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

void	fill_z_matrix(char *file_name, t_fdf *data)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file_name, O_RDONLY, 0);
	if (fd < 0)
		return ;
	if (allocate_z_matrix(data) == -1)
	{
		close(fd);
		return ;
	}
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		fill_matrix(data->z_matrix[i], line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
}

void	read_file(char *file_name, t_fdf *data)
{
	get_dimensions(file_name, data);
	fill_z_matrix(file_name, data);
}
