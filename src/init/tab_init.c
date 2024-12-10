/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:51:22 by samberna          #+#    #+#             */
/*   Updated: 2024/12/09 23:52:37 by samberna         ###   ########.fr       */
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
	while ((line = _gnl_get_next_line(fd)))
	{
		lines++;
		free(line);
	}
	close(fd);
	return (lines);
}

static void _fdf_free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int _fdf_tab_count_columns(char *file)
{
	int		fd;
	int		columns;
	char	*line;
	char	**split_line;
	
	columns = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	if ((line = _gnl_get_next_line(fd)))
	{
		split_line = ft_split(line, ' ');
		while (split_line[columns])
			columns++;
		free(line);
		_fdf_free_split(split_line);
	}
	while ((line = _gnl_get_next_line(fd)))
	{
		split_line = ft_split(line, ' ');
		int current_columns = 0;
		while (split_line[current_columns])
			current_columns++;
		if (columns != current_columns)
		{
			free(line);
			_fdf_free_split(split_line);
			close(fd);
			return (0);
		}
		free(line);
		_fdf_free_split(split_line);
	}
	close(fd);
	return (columns);
}

void	_fdf_tab_init(t_fdf *fdf, char *file)
{
	int i;

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
	i = 0;
	while (i < fdf->lines && (fdf->tab[i] = (t_point *)malloc(sizeof(t_point) * fdf->columns)))
		i++;
	if (i != fdf->lines)
	{
		ft_putstr_fd("Error: Malloc Failed\n", 1);
		exit(0);
	}
}