/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:53:05 by samberna          #+#    #+#             */
/*   Updated: 2024/12/10 19:13:59 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	_fdf_mlx_draw_pixel(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= _FDF_WIDTH || y < 0 || y >= _FDF_HEIGHT)
		return ;
	dst = fdf->img->addr + (y * fdf->img->line_length + x * (fdf->img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static int	_fdf_get_gradient_color(t_point point1, t_point point2, t_point current)
{
	float	percentage;
	int		red;
	int		green;
	int		blue;

	if (point1.draw_x == point2.draw_x)
		percentage = (float)(current.draw_y - point1.draw_y) / (point2.draw_y - point1.draw_y);
	else
		percentage = (float)(current.draw_x - point1.draw_x) / (point2.draw_x - point1.draw_x);
	red = (int)((1 - percentage) * ((point1.color >> 16) & 0xFF) + percentage * ((point2.color >> 16) & 0xFF));
	green = (int)((1 - percentage) * ((point1.color >> 8) & 0xFF) + percentage * ((point2.color >> 8) & 0xFF));
	blue = (int)((1 - percentage) * (point1.color & 0xFF) + percentage * (point2.color & 0xFF));
	return ((red << 16) | (green << 8) | blue);
}

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

void	_fdf_mlx_draw_line_gradient(t_fdf *fdf, t_point point1, t_point point2)
{
	t_line	line;
	t_point	current;

	fill_line_struct(&line, point1, point2);
	current = point1;
	while (current.draw_x != point2.draw_x || current.draw_y != point2.draw_y)
	{
		_fdf_mlx_draw_pixel(fdf, current.draw_x, current.draw_y, _fdf_get_gradient_color(point1, point2, current));
		line.error2 = line.error * 2;
		if (line.error2 > -line.delta_y)
		{
			line.error -= line.delta_y;
			current.draw_x += line.sign_x;
		}
		if (line.error2 < line.delta_x)
		{
			line.error += line.delta_x;
			current.draw_y += line.sign_y;
		}
	}
	_fdf_mlx_draw_pixel(fdf, current.draw_x, current.draw_y, point2.color);
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
