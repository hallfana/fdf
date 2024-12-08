/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:46:48 by hallfana          #+#    #+#             */
/*   Updated: 2024/12/08 20:06:18 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx_linux/mlx.h"
#include "fdf.h"
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
	//void	*mlx_win;
	void	*img;

	mlx = mlx_init();
	//mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	/*for(int x = 10; x < 1200; x+=10)
	{
		int rgb = generate_rgb();
		for (int x2 = 0; x2 < 10; x2++)
		{
			for (int y = 10 ; y < 200 ; y++)
			{
				mlx_pixel_put(mlx, mlx_win, x + x2, y, rgb);
			}
		}
	}*/
	img = mlx_new_image(mlx, 1920, 1080);
	(void)img;
	mlx_loop(mlx);
}
