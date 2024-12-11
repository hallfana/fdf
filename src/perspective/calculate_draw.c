/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:43:50 by samberna          #+#    #+#             */
/*   Updated: 2024/12/11 13:40:47 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

t_point	_fdf_calculate_iso(t_fdf *fdf, int i, int j)
{
	t_point	point;
	float	scaled_x;
	float	scaled_y;
	float	scaled_z;

	scaled_x = fdf->tab[i][j].origin_x * fdf->zoom;
	scaled_y = fdf->tab[i][j].origin_y * fdf->zoom;
	scaled_z = fdf->tab[i][j].origin_z * fdf->zoom;
	point.draw_x = (scaled_x - scaled_y) * cos(0.523599);
	point.draw_y = -scaled_z + (scaled_x + scaled_y) * sin(0.523599);
	point.draw_z = scaled_z;
	point.color = fdf->tab[i][j].color;
	return (point);
}

static void	_fdf_t_offset_init(t_offset *offset)
{
	offset->i = 0;
	offset->j = 0;
	offset->min_x = INT_MAX;
	offset->max_x = INT_MIN;
	offset->min_y = INT_MAX;
	offset->max_y = INT_MIN;
}

static void	_fdf_calculate_offset(t_fdf *fdf,
	t_point (*func_draw)(t_fdf *, int, int), int *offset_x, int *offset_y)
{
	t_offset	of;
	t_point		point;

	_fdf_t_offset_init(&of);
	of.i = 0;
	while (of.i < fdf->lines)
	{
		of.j = 0;
		while (of.j < fdf->columns)
		{
			point = func_draw(fdf, of.i, of.j);
			if (point.draw_x < of.min_x)
				of.min_x = point.draw_x;
			if (point.draw_x > of.max_x)
				of.max_x = point.draw_x;
			if (point.draw_y < of.min_y)
				of.min_y = point.draw_y;
			if (point.draw_y > of.max_y)
				of.max_y = point.draw_y;
			of.j++;
		}
		of.i++;
	}
	*offset_x = (_FDF_WIDTH - (of.max_x - of.min_x)) / 2 - of.min_x;
	*offset_y = (_FDF_HEIGHT - (of.max_y - of.min_y)) / 2 - of.min_y;
}

void	_fdf_calculate_draw(t_fdf *fdf, t_point (*func_draw)(t_fdf *, int, int))
{
	int		i;
	int		j;
	int		offset_x;
	int		offset_y;
	t_point	point;

	_fdf_calculate_offset(fdf, func_draw, &offset_x, &offset_y);
	i = 0;
	while (i < fdf->lines)
	{
		j = 0;
		while (j < fdf->columns)
		{
			point = func_draw(fdf, i, j);
			fdf->tab[i][j].draw_x = point.draw_x + offset_x;
			fdf->tab[i][j].draw_y = point.draw_y + offset_y;
			fdf->tab[i][j].draw_z = point.draw_z;
			fdf->tab[i][j].color = point.color;
			j++;
		}
		i++;
	}
}
