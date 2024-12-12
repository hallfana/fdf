/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_fdf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:38:45 by samberna          #+#    #+#             */
/*   Updated: 2024/12/12 18:04:05 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_FDF_H
# define STRUCT_FDF_H

typedef struct s_gnl
{
	char	*buf;
	ssize_t	pos;
	int		tab;
	int		c;
}	t_gnl;

typedef struct s_point
{
	int		origin_x;
	int		origin_y;
	int		origin_z;
	int		draw_x;
	int		draw_y;
	int		draw_z;
	int		color;
}	t_point;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_line
{
	int		delta_x;
	int		delta_y;
	int		sign_x;
	int		sign_y;
	int		error;
	int		error2;
}				t_line;

typedef struct s_offset
{
	int		i;
	int		j;
	int		min_x;
	int		max_x;
	int		min_y;
	int		max_y;
}				t_offset;

typedef struct s_fdf
{
	void		*mlx;
	void		*win;
	t_point		**tab;
	int			lines;
	int			columns;
	t_img		*img;
	float		zoom;
}				t_fdf;

#endif