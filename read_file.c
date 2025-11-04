/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajesus- <dajesus-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:11:16 by dajesus-          #+#    #+#             */
/*   Updated: 2025/01/10 11:29:53 by dajesus-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	count_columns(char *line, char delimiter)
{
	int	i;
	int	column_count;

	i = 0;
	column_count = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == delimiter)
		{
			while (line[i] && (line[i] == delimiter || line[i] == '\n'))
				i++;
		}
		else
		{
			while (line[i] && line[i] != delimiter)
				i++;
			column_count++;
		}
	}
	return (column_count);
}

static int	process_lines(int fd, t_fdf *data)
{
	char	*line;
	int		lines_count;
	int		columns;
	int		flag;

	lines_count = 0;
	flag = 0;
	line = get_next_line(fd);
	validate_line(line, data, fd);
	data->width = count_columns(line, ' ');
	while (line)
	{
		columns = count_columns(line, ' ');
		if (data->width != columns)
			flag = 1;
		lines_count++;
		free(line);
		line = get_next_line(fd);
	}
	if (flag)
		cleanup_and_exit(data, fd, line, 1);
	return (lines_count);
}

static void	get_dimensions(char *file_name, t_fdf *data)
{
	int	fd;

	validate_file_extension(file_name);
	fd = open_file(file_name);
	data->height = process_lines(fd, data);
	close(fd);
}

void	read_file(char *file_name, t_fdf *data)
{
	get_dimensions(file_name, data);
	fill_z_and_color_matrix(file_name, data);
}
