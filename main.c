/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:46:48 by hallfana          #+#    #+#             */
/*   Updated: 2024/12/08 19:42:30 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx_linux/mlx.h"
#include <math.h>

int generate_rgb()
{
	static int i = 0;
	int m_pi = 3.14159265358979323846;
 
	int red = (128.0 + sin(i * 2 * m_pi / 256 + 0.0) * 127.0);
	int green = (128.0 + sin(i * 2 * m_pi / 256 + 2 * m_pi / 3.0) * 127.0);
	int blue = (128.0 + sin(i * 2 * m_pi / 256 + 4 * m_pi / 3.0) * 127.0);

	i++;
	if (i >= 256)
		i = 0;
	return (red << 16 | green << 8 | blue);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	for(int x = 10; x < 200; x++)
	{
		for (int y = 10 ; y < 50 ; y++)
		{
			mlx_pixel_put(mlx, mlx_win, x, y, generate_rgb(0, 150, 150, 150));
		}
	}
	mlx_loop(mlx);
}
