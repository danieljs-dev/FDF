/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajesus- <dajesus-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:09:15 by dajesus-          #+#    #+#             */
/*   Updated: 2025/01/10 11:29:58 by dajesus-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	cleanup_and_exit(t_fdf *data, int fd, char *line, int code)
{
	if (line)
		free(line);
	if (data)
		free(data);
	if (fd >= 0)
		close(fd);
	exit(code);
}

void	validate_file_extension(char *file_name)
{
	if (!ft_strnstr(file_name, ".fdf", ft_strlen(file_name)))
		exit(1);
}

void	validate_line(char *line, t_fdf *data, int fd)
{
	if (!line)
		cleanup_and_exit(data, fd, line, 1);
}
