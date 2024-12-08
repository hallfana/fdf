/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:46:48 by hallfana          #+#    #+#             */
/*   Updated: 2024/12/09 00:12:48 by samberna         ###   ########.fr       */
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
	int r = (int)(sin(0.01 * i + 0) * 127 + 128);
	int g = (int)(sin(0.01 * i + 2) * 127 + 128);
	int b = (int)(sin(0.01 * i + 4) * 127 + 128);
	i++;
	return create_trgb(0, r, g, b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_data gen_rgb_img(void *mlx)
{
	t_data img;
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	for(int x = 10; x < 1200; x+=2)
	{
		int rgb = generate_rgb();
		for (int x2 = 0; x2 < 2; x2++)
		{
			for (int y = 10 ; y < 200 ; y++)
			{
				my_mlx_pixel_put(&img, x + x2, y, rgb);
			}
		}
	}
	return img;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 500, 500, "Hello world!");

	img = gen_rgb_img(mlx);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	
	mlx_loop(mlx);
}
