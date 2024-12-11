/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:51:22 by samberna          #+#    #+#             */
/*   Updated: 2024/12/11 14:18:43 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static int	_fdf_tab_count_lines(char *file)
{
	int		fd;
	int		lines;
	char	*line;

	lines = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	line = _gnl_get_next_line(fd);
	while (line)
	{
		lines++;
		free(line);
		line = _gnl_get_next_line(fd);
	}
	free(line);
	close(fd);
	return (lines);
}

static void	_fdf_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

typedef struct s_file_info
{
	int		fd;
	int		columns;
	char	*line;
	char	**split_line;
}	t_file_info;

static int	_fdf_tab_count_columns(char *file)
{
	t_file_info	info;

	info.columns = 0;
	info.fd = open(file, O_RDONLY);
	if (info.fd < 0)
		return (0);
	info.line = _gnl_get_next_line(info.fd);
	if (info.line)
	{
		info.split_line = ft_split(info.line, ' ');
		while (info.split_line[info.columns])
			info.columns++;
		free(info.line);
		_fdf_free_split(info.split_line);
	}
	close(info.fd);
	return (info.columns);
}
/*
static int	_fdf_validate_columns(char *file, int columns)
{
	t_file_info	info;
	int			current_columns;

	info.fd = open(file, O_RDONLY);
	if (info.fd < 0)
		return (0);
	info.line = _gnl_get_next_line(info.fd);
	free(info.line);
	info.line = _gnl_get_next_line(info.fd);
	while (info.line)
	{
		info.split_line = ft_split(info.line, ' ');
		current_columns = 0;
		while (info.split_line[current_columns])
			current_columns++;
		if (columns != current_columns)
		{
			free(info.line);
			_fdf_free_split(info.split_line);
			close(info.fd);
			return (0);
		}
		free(info.line);
		_fdf_free_split(info.split_line);
		info.line = _gnl_get_next_line(info.fd);
	}
	free(info.line);
	close(info.fd);
	return (1);
}*/

void	_fdf_tab_init(t_fdf *fdf, char *file)
{
	int	i;

	fdf->lines = _fdf_tab_count_lines(file);
	fdf->columns = _fdf_tab_count_columns(file);
	if (fdf->lines == 0 || fdf->columns == 0)
	{
		ft_putstr_fd("Error: Invalid File\n", 1);
		exit(0);
	}
	fdf->tab = (t_point **)malloc(sizeof(t_point *) * fdf->lines);
	if (!fdf->tab)
	{
		ft_putstr_fd("Error: Malloc Failed\n", 1);
		exit(0);
	}
	i = -1;
	while (++i < fdf->lines)
		fdf->tab[i] = (t_point *)malloc(sizeof(t_point) * fdf->columns);
	if (i != fdf->lines)
	{
		ft_putstr_fd("Error: Malloc Failed\n", 1);
		exit(0);
	}
}
