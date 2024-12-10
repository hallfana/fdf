/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:53:05 by samberna          #+#    #+#             */
/*   Updated: 2024/12/10 19:05:59 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	_fdf_mlx_draw_pixel(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= _FDF_WIDTH || y < 0 || y >= _FDF_HEIGHT)
		return ;
	printf("x: %d, y: %d, color: %d\n", x, y, color);
	dst = fdf->img->addr + (y * fdf->img->line_length + x * (fdf->img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/*static int interpolate_color(int color1, int color2, float t)
{
    int r1 = (color1 >> 16) & 0xFF;
    int g1 = (color1 >> 8) & 0xFF;
    int b1 = color1 & 0xFF;
    
    int r2 = (color2 >> 16) & 0xFF;
    int g2 = (color2 >> 8) & 0xFF;
    int b2 = color2 & 0xFF;

    int r = r1 + (r2 - r1) * t;
    int g = g1 + (g2 - g1) * t;
    int b = b1 + (b2 - b1) * t;

    return (r << 16) | (g << 8) | b;
}*/

static void	fill_line_struct(t_line *line, t_point point1, t_point point2)
{
	line->delta_x = abs(point2.draw_x - point1.draw_x);
	line->delta_y = abs(point2.draw_y - point1.draw_y);
	if (point1.draw_x < point2.draw_x)
		line->sign_x = 1;
	else
		line->sign_x = -1;
	if (point1.draw_y < point2.draw_y)
		line->sign_y = 1;
	else
		line->sign_y = -1;
	line->error = line->delta_x - line->delta_y;
}

void	_fdf_mlx_draw_line(t_fdf *fdf, t_point point1, t_point point2)
{
	t_line	line;

	fill_line_struct(&line, point1, point2);
	while (point1.draw_x != point2.draw_x || point1.draw_y != point2.draw_y)
	{
		_fdf_mlx_draw_pixel(fdf, point1.draw_x, point1.draw_y, point1.color);
		line.error2 = line.error * 2;
		if (line.error2 > -line.delta_y)
		{
			line.error -= line.delta_y;
			point1.draw_x += line.sign_x;
		}
		if (line.error2 < line.delta_x)
		{
			line.error += line.delta_x;
			point1.draw_y += line.sign_y;
		}
	}
}
