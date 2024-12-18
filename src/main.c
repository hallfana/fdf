/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:35:39 by samberna          #+#    #+#             */
/*   Updated: 2024/12/12 18:10:50 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
	{
		ft_putstr_fd("Error: Missing Arguments\n", 1);
		return (0);
	}
	_fdf_mlx_init(&fdf);
	_fdf_tab_init(&fdf, argv[1]);
	_fdf_tab_populate(&fdf, argv[1]);
	fdf.img = malloc(sizeof(t_img));
	fdf.img->img = mlx_new_image(fdf.mlx, _FDF_WIDTH, _FDF_HEIGHT);
	if (!fdf.img->img)
	{
		ft_putstr_fd("Error: Failed to create new image\n", 1);
		return (0);
	}
	_fdf_calculate_draw(&fdf, &_fdf_calculate_iso);
	_fdf_display(&fdf);
	mlx_hook(fdf.win, 2, 1L << 0, _fdf_key_hook, &fdf);
	mlx_hook(fdf.win, 17, 1L << 17, _fdf_exit, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
