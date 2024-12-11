/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 00:04:44 by samberna          #+#    #+#             */
/*   Updated: 2024/12/11 14:52:50 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void _fdf_exit(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img->img);
	mlx_destroy_window(fdf->mlx, fdf->win);
	while (fdf->lines--)
		free(fdf->tab[fdf->lines]);
	free(fdf->tab);
	free(fdf->img);
	free(fdf);
	exit(0);
}

int	_fdf_key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == 65307)
	{
		_fdf_exit(fdf);
		return (0);
	}
	if (keycode == 65362)
	{
		fdf->zoom *= 1.1;
		_fdf_calculate_draw(fdf, &_fdf_calculate_iso);
		_fdf_display(fdf);
	}
	else if (keycode == 65364)
	{
		fdf->zoom *= 0.9;
		_fdf_calculate_draw(fdf, &_fdf_calculate_iso);
		_fdf_display(fdf);
	}
	return (0);
}
