/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:46:48 by hallfana          #+#    #+#             */
/*   Updated: 2024/12/08 19:55:19 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx_linux/mlx.h"
#include <math.h>

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int generate_rgb()
{
	// get all the rgb color from the gratient each time i call the function
	static int i = 0;
	int r = (int)(sin(0.3 * i + 0) * 127 + 128);
	int g = (int)(sin(0.3 * i + 2) * 127 + 128);
	int b = (int)(sin(0.3 * i + 4) * 127 + 128);
	i++;
	return create_trgb(0, r, g, b);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	for(int x = 10; x < 1200; x+=2)
	{
		int rgb = generate_rgb();
		for (int y = 10 ; y < 200 ; y++)
		{
			mlx_pixel_put(mlx, mlx_win, x, y, rgb);
		}
		for (int y = 10 ; y < 200 ; y++)
		{
			mlx_pixel_put(mlx, mlx_win, x + 1, y, rgb);
		}
	}
	mlx_loop(mlx);
}
