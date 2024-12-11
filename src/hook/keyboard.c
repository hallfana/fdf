/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 00:04:44 by samberna          #+#    #+#             */
/*   Updated: 2024/12/11 14:42:50 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

int	_fdf_key_hook(int keycode, t_fdf *fdf)
{
	printf("keycode: %d\n", keycode);
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
