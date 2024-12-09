/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallfana <hallfana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:43:01 by hallfana          #+#    #+#             */
/*   Updated: 2024/12/09 16:52:00 by hallfana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int keyboardHandler(int code, t_fdf *fdf)
{
	if (code == 65307)
	{
		mlx_destroy_window(fdf->mlx, fdf->mlx_win);
		exit(1);
	}
	/*if (code == 114)
	{
		t_data img = gen_rgb_img(fdf->mlx);
		mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, img.img, 0, 0);
	}*/
	return (0);
}
