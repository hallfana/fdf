/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:43:50 by samberna          #+#    #+#             */
/*   Updated: 2024/12/10 19:10:52 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*static int create_gradient(int z, int min_z, int max_z)
{
    float t = (float)(z - min_z) / (max_z - min_z);
    if (t < 0) t = 0;
    if (t > 1) t = 1;
    int r, g, b;
    if (t < 0.5) {
        float s = t * 2;
        r = ((_FDF_NEUTRAL >> 16) & 0xFF) * s + ((_FDF_COLD >> 16) & 0xFF) * (1 - s);
        g = ((_FDF_NEUTRAL >> 8) & 0xFF) * s + ((_FDF_COLD >> 8) & 0xFF) * (1 - s);
        b = (_FDF_NEUTRAL & 0xFF) * s + (_FDF_COLD & 0xFF) * (1 - s);
    } else {
        float s = (t - 0.5) * 2;
        r = ((_FDF_HOT >> 16) & 0xFF) * s + ((_FDF_NEUTRAL >> 16) & 0xFF) * (1 - s);
        g = ((_FDF_HOT >> 8) & 0xFF) * s + ((_FDF_NEUTRAL >> 8) & 0xFF) * (1 - s);
        b = (_FDF_HOT & 0xFF) * s + (_FDF_NEUTRAL & 0xFF) * (1 - s);
    }
    return (r << 16) | (g << 8) | b;
}*/

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
    //point.color = create_gradient(fdf->tab[i][j].origin_z, 0, 10);
	point.color = fdf->tab[i][j].color;
    return (point);
}

static void	_fdf_calculate_offset(t_fdf *fdf, t_point (*func_draw)(t_fdf *, int, int), int *offset_x, int *offset_y)
{
	int		i;
	int		j;
	int		min_x = INT_MAX;
	int		max_x = INT_MIN;
	int		min_y = INT_MAX;
	int		max_y = INT_MIN;
	t_point	point;

	i = 0;
	while (i < fdf->lines)
	{
		j = 0;
		while (j < fdf->columns)
		{
			point = func_draw(fdf, i, j);
			if (point.draw_x < min_x) min_x = point.draw_x;
			if (point.draw_x > max_x) max_x = point.draw_x;
			if (point.draw_y < min_y) min_y = point.draw_y;
			if (point.draw_y > max_y) max_y = point.draw_y;
			j++;
		}
		i++;
	}
	*offset_x = (_FDF_WIDTH - (max_x - min_x)) / 2 - min_x;
	*offset_y = (_FDF_HEIGHT - (max_y - min_y)) / 2 - min_y;
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
