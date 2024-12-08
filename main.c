/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:46:48 by hallfana          #+#    #+#             */
/*   Updated: 2024/12/08 19:52:17 by samberna         ###   ########.fr       */
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
	// generate rgb gradient for each pixel of my banner
	// fix the code i have a grey banner

	int r = (int)(sin(0.1) * 127 + 128);
	int g = (int)(sin(0.2) * 127 + 128);
	int b = (int)(sin(0.3) * 127 + 128);
	return (create_trgb(0, r, g, b));
	
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	for(int x = 10; x < 600; x++)
	{
		for (int y = 10 ; y < 100 ; y++)
		{
			mlx_pixel_put(mlx, mlx_win, x, y, generate_rgb());
		}
	}
	mlx_loop(mlx);
}
