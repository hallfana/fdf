/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_populate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:25:23 by samberna          #+#    #+#             */
/*   Updated: 2024/12/11 13:49:46 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static void	_fdf_line_populate(t_fdf *fdf, char *line, int i)
{
	char	**split;
	char	**t;
	int		j;

	split = ft_split(line, ' ');
	j = 0;
	while (split[j])
	{
		t = ft_split(split[j], ',');
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
	}
}

void	_fdf_tab_populate(t_fdf *fdf, char *file)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return ;
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
