/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:46:48 by hallfana          #+#    #+#             */
/*   Updated: 2024/12/09 03:12:58 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf *fdf;

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

void	my_mlx_line_put(t_data img, int x1, int y1, int x2, int y2)
{
	int dx = abs(x2 - x1);
	int sx = x1 < x2 ? 1 : -1;
	int dy = -abs(y2 - y1);
	int sy = y1 < y2 ? 1 : -1;
	int err = dx + dy;

	while (1)
	{
		my_mlx_pixel_put(&img, x1, y1, create_trgb(0, 125, 0, 125));
		if (x1 == x2 && y1 == y2)
			break;
		int e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x1 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}

t_data gen_rgb_img(void *mlx)
{
	t_data img;
	img.img = mlx_new_image(mlx, WINX, WINY);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	for(int x = 0; x < 500; x+=1)
	{
		int rgb = generate_rgb();
		for (int x2 = 0; x2 < 1; x2++)
		{
			for (int y = 0 ; y < 250 ; y++)
			{
				my_mlx_pixel_put(&img, x + x2, y, rgb);
			}
		}
	}
	return img;
}

int keyboardHandler(int code)
{
	//ESC 65307
	//r 114

	if (code == 65307)
	{
		mlx_destroy_window(fdf->mlx, fdf->mlx_win);
		free(fdf->mlx);
		free(fdf);
		exit(1);
	}
	/*if (code == 114)
	{
		t_data img = gen_rgb_img(fdf->mlx);
		mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, img.img, 0, 0);
	}*/
	return (0);
}

int  isometric_format_x(int x, int y, int z)
{
	int tmp;

	tmp = x;
	(void)z;
	return (tmp - y) * cos(0.523599);
}

int  isometric_format_y(int x, int y, int z)
{
	int tmp;

	tmp = x;
	return (tmp + y) * sin(0.523599) - z;
}

int	main(int argc, char **argv)
{
	t_data	img;
	t_tab	tab;
	fdf = malloc(sizeof(t_fdf));

	(void)argc;
	fdf->mlx = mlx_init();
	fdf->mlx_win = mlx_new_window(fdf->mlx, WINX, WINY, "Hello world!");

	img.img = mlx_new_image(fdf->mlx, WINX, WINY);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	//img = gen_rgb_img(fdf->mlx);
	//mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, img.img, 0, 0);

	tab.width = 19;
	tab.height = 12;
	tab.tab = malloc(sizeof(t_point *) * tab.height);
	for (int i = 0; i < tab.height; i++)
	{
		tab.tab[i] = malloc(sizeof(t_point) * tab.width);
	}

	int fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	int i = 0;
	int j = 0;
	char *line;
	while ((line = get_next_line(fd)))
	{
		char **split = ft_split(line, ' ');
		for (j = 0; j < tab.width; j++)
		{
			tab.tab[i][j].x = j * 20;
			tab.tab[i][j].y = i * 20;
			tab.tab[i][j].z = ft_atoi(split[j]);
			tab.tab[i][j].color = create_trgb(0, 125, 125, 125);
		}
		i++;
	}

	printf("fd: %d\n", fd);	
 
	int offset_x = isometric_format_x(tab.tab[0][0].x, tab.tab[0][0].y, tab.tab[0][0].z) -
		isometric_format_x(tab.tab[tab.height - 1][tab.width - 1].x, tab.tab[tab.height - 1][tab.width - 1].y, tab.tab[tab.height - 1][tab.width - 1].z);
	int offset_y = isometric_format_y(tab.tab[0][0].x, tab.tab[0][0].y, tab.tab[0][0].z) -
		isometric_format_y(tab.tab[tab.height - 1][tab.width - 1].x, tab.tab[tab.height - 1][tab.width - 1].y, tab.tab[tab.height - 1][tab.width - 1].z);
		
	// draw the points
	for (int i = 0; i < tab.height; i++)
	{
		for (int j = 0; j < tab.width; j++)
		{

			my_mlx_pixel_put(
				&img,
				isometric_format_x(tab.tab[i][j].x, tab.tab[i][j].y, tab.tab[i][j].z) + WINX / 2 - offset_x / 2,
				isometric_format_y(tab.tab[i][j].x, tab.tab[i][j].y, tab.tab[i][j].z) + WINY / 2 - offset_y / 2,
				tab.tab[i][j].color
			);
		}
	}
	
	/*my_mlx_line_put(
		img,
		isometric_format_x(tab.tab[0][0].x, tab.tab[0][0].y, tab.tab[0][0].z) + 500,
		isometric_format_y(tab.tab[0][0].x, tab.tab[0][0].y, tab.tab[0][0].z) + 500,
		isometric_format_x(tab.tab[2][1].x, tab.tab[2][1].y, tab.tab[2][1].z) + 500,
		isometric_format_y(tab.tab[2][1].x, tab.tab[2][1].y, tab.tab[2][1].z) + 500
	);*/
	// Connect each point to the adjacent points
	/*for (int m = 0; m < tab.height; m++)
	{
		for (int n = 0; n < tab.width; n++)
		{
			if (n < tab.width - 1)
			{
				int x1 = isometric_format_x(tab.tab[m][n].x, tab.tab[m][n].y, tab.tab[m][n].z) + WINX / 2;
				int y1 = isometric_format_y(tab.tab[m][n].x, tab.tab[m][n].y, tab.tab[m][n].z) + WINY / 2;
				int x2 = isometric_format_x(tab.tab[m][n + 1].x, tab.tab[m][n + 1].y, tab.tab[m][n + 1].z) + WINX / 2;
				int y2 = isometric_format_y(tab.tab[m][n + 1].x, tab.tab[m][n + 1].y, tab.tab[m][n + 1].z) + WINY / 2;
				my_mlx_line_put(img, x1, y1, x2, y2);
			}
			if (m < tab.height - 2)
			{
				int x1 = isometric_format_x(tab.tab[m][n].x, tab.tab[m][n].y, tab.tab[m][n].z) + WINX / 2;
				int y1 = isometric_format_y(tab.tab[m][n].x, tab.tab[m][n].y, tab.tab[m][n].z) + WINY / 2;
				int x2 = isometric_format_x(tab.tab[m + 1][n].x, tab.tab[m + 1][n].y, tab.tab[m + 1][n].z) + WINX / 2;
				int y2 = isometric_format_y(tab.tab[m + 1][n].x, tab.tab[m + 1][n].y, tab.tab[m + 1][n].z) + WINY / 2;
				my_mlx_line_put(img, x1, y1, x2, y2);
			}
		}
	}*/

	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, img.img, 0, 0);
	
	mlx_hook(fdf->mlx_win, 2, 1L<<0, keyboardHandler, fdf->mlx);
	mlx_loop(fdf->mlx);
}
