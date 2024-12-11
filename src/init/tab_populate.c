/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_populate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:25:23 by samberna          #+#    #+#             */
/*   Updated: 2024/12/11 14:15:55 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static void	_fdf_line_populate(t_fdf *fdf, char *line, int i)
{
	char	**split;
	char	**t;
	int		j;

	split = ft_split(line, ' ');
	if (!split)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 1);
		exit(1);
	}
	j = 0;
	while (split[j])
	{
		t = ft_split(split[j], ',');
		if (!t)
		{
			ft_putstr_fd("Error: Memory allocation failed\n", 1);
			exit(1);
		}
		fdf->tab[i][j].origin_x = j * 20;
		fdf->tab[i][j].origin_y = i * 20;
		fdf->tab[i][j].origin_z = ft_atoi(t[0]);
		fdf->tab[i][j].draw_x = 0;
		fdf->tab[i][j].draw_y = 0;
		fdf->tab[i][j].draw_z = 0;
		if (t[1])
			fdf->tab[i][j].color = _fdf_atoi_base(t[1] + 2, "0123456789ABCDEF");
		else
			fdf->tab[i][j].color = 0xFFFFFF;
		j++;
		// Free the split array
		for (int k = 0; t[k]; k++)
			free(t[k]);
		free(t);
	}
	// Free the split array
	for (int k = 0; split[k]; k++)
		free(split[k]);
	free(split);
}

void	_fdf_tab_populate(t_fdf *fdf, char *file)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Failed to open file\n", 1);
		exit(1);
	}
	line = _gnl_get_next_line(fd);
	while (line)
	{
		_fdf_line_populate(fdf, line, i);
		free(line);
		i++;
		line = _gnl_get_next_line(fd);
	}
	free(line);
	close(fd);
}
