/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:51:22 by samberna          #+#    #+#             */
/*   Updated: 2024/12/11 14:10:08 by samberna         ###   ########.fr       */
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

static int	_fdf_tab_count_columns(char *file)
{
	int		fd;
	int		columns;
	char	*line;
	char	**split_line;

	columns = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	line = _gnl_get_next_line(fd);
	if (line)
	{
		split_line = ft_split(line, ' ');
		if (split_line)
		{
			while (split_line[columns])
				columns++;
			_fdf_free_split(split_line);
		}
		free(line);
	}
	close(fd);
	return (columns);
}

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
