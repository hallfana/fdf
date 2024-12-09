/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:46:48 by hallfana          #+#    #+#             */
/*   Updated: 2024/12/09 20:32:20 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf *fdf;

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
			tab.tab[i][j].color = generate_rgb();
		}
		i++;
	}
	
	// draw the points
	int offset_x = WINX / 2 - isometric_format_x(tab.tab[tab.height / 2][tab.width / 2].x, tab.tab[tab.height / 2][tab.width / 2].y, tab.tab[tab.height / 2][tab.width / 2].z);
	int offset_y = WINY / 2 - isometric_format_y(tab.tab[tab.height / 2][tab.width / 2].x, tab.tab[tab.height / 2][tab.width / 2].y, tab.tab[tab.height / 2][tab.width / 2].z);

	for (int i = 0; i < tab.height; i++)
	{
		for (int j = 0; j < tab.width; j++)
		{
			my_mlx_pixel_put(
				&img,
				isometric_format_x(tab.tab[i][j].x, tab.tab[i][j].y, tab.tab[i][j].z) + offset_x,
				isometric_format_y(tab.tab[i][j].x, tab.tab[i][j].y, tab.tab[i][j].z) + offset_y,
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
	for (int m = 0; m < tab.height; m++)
	{
		for (int n = 0; n < tab.width; n++)
		{
			if (n < tab.width - 1)
			{
				int x1 = isometric_format_x(tab.tab[m][n].x, tab.tab[m][n].y, tab.tab[m][n].z) + offset_x;
				int y1 = isometric_format_y(tab.tab[m][n].x, tab.tab[m][n].y, tab.tab[m][n].z) + offset_y;
				int x2 = isometric_format_x(tab.tab[m][n + 1].x, tab.tab[m][n + 1].y, tab.tab[m][n + 1].z) + offset_x;
				int y2 = isometric_format_y(tab.tab[m][n + 1].x, tab.tab[m][n + 1].y, tab.tab[m][n + 1].z) + offset_y;
				my_mlx_line_put(img, x1, y1, x2, y2);
			}
			if (m < tab.height - 2)
			{
				int x1 = isometric_format_x(tab.tab[m][n].x, tab.tab[m][n].y, tab.tab[m][n].z) + offset_x;
				int y1 = isometric_format_y(tab.tab[m][n].x, tab.tab[m][n].y, tab.tab[m][n].z) + offset_y;
				int x2 = isometric_format_x(tab.tab[m + 1][n].x, tab.tab[m + 1][n].y, tab.tab[m + 1][n].z) + offset_x;
				int y2 = isometric_format_y(tab.tab[m + 1][n].x, tab.tab[m + 1][n].y, tab.tab[m + 1][n].z) + offset_y;
				my_mlx_line_put(img, x1, y1, x2, y2);
			}
		}
	}

	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, img.img, 0, 0);
	
	mlx_hook(fdf->mlx_win, 2, 1L<<0, keyboardHandler, fdf->mlx);
	mlx_loop(fdf->mlx);
}
