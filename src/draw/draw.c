/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:59:53 by samberna          #+#    #+#             */
/*   Updated: 2024/12/10 19:14:35 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	_fdf_draw_points(t_fdf *fdf)
{
	int		i;
	int		j;

	i = 0;
	while (i < fdf->lines)
	{
		j = 0;
		while (j < fdf->columns)
		{
			_fdf_mlx_draw_pixel(fdf, fdf->tab[i][j].draw_x, fdf->tab[i][j].draw_y, fdf->tab[i][j].color);
			j++;
		}
		i++;
	}
}

static void	_fdf_draw_lines(t_fdf *fdf)
{
	int		i;
	int		j;

	i = 0;
	while (i < fdf->lines)
	{
		j = 0;
		while (j < fdf->columns)
		{
			if (j + 1 < fdf->columns)
				_fdf_mlx_draw_line_gradient(fdf, fdf->tab[i][j], fdf->tab[i][j + 1]);
			if (i + 1 < fdf->lines)
				_fdf_mlx_draw_line_gradient(fdf, fdf->tab[i][j], fdf->tab[i + 1][j]);
			j++;
		}
		i++;
	}
}

void	_fdf_display(t_fdf *fdf)
{
	/*if (!fdf->img)
	{
		ft_putstr_fd("Error: Image structure not initialized\n", 1);
		return;
	}
	if (fdf->img->img)
		mlx_destroy_image(fdf->mlx, fdf->img->img);*/
	fdf->img->img = mlx_new_image(fdf->mlx, _FDF_WIDTH, _FDF_HEIGHT);
	if (!fdf->img->img)
	{
		ft_putstr_fd("Error: Failed to create new image\n", 1);
		return;
	}
	fdf->img->addr = mlx_get_data_addr(fdf->img->img, &fdf->img->bits_per_pixel, &fdf->img->line_length, &fdf->img->endian);
	_fdf_draw_points(fdf);
	_fdf_draw_lines(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->img, 0, 0);
}