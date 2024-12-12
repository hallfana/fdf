/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:37:07 by samberna          #+#    #+#             */
/*   Updated: 2024/12/12 18:22:43 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <sys/types.h>
# include <limits.h>

# include "./struct_fdf.h"
# include "./libft.h"
# include "./mlx.h"

# define _FDF_WIDTH 1000
# define _FDF_HEIGHT 1000
# define _GNL_BUFFER_SIZE 8192
# define _FDF_COLD 0x0000FF
# define _FDF_NEUTRAL 0xFFFFFF
# define _FDF_HOT 0xFF5500

/* get_next_line */
char	*_gnl_get_next_line(int fd);
int		gnl_strlen(const char *s, char end);
int		line_counter(const char *str);
void	cpy_len(const char *src, char *dest, int len);
char	*gnl_strdup(const char *s, char end);
char	*gnl_strjoin(char *s1, char *s2);

/* init */
void	_fdf_mlx_init(t_fdf *fdf);
void	_fdf_free_split(char **split);
void	_fdf_tab_init(t_fdf *fdf, char *file);
void	_fdf_tab_populate(t_fdf *fdf, char *file);

/* perspective */
void	_fdf_calculate_draw(t_fdf *fdf,
			t_point (*func_draw)(t_fdf *, int, int));
t_point	_fdf_calculate_iso(t_fdf *fdf, int i, int j);

/* draw */
void	_fdf_mlx_draw_pixel(t_fdf *fdf, int x, int y, int color);
void	_fdf_mlx_draw_line(t_fdf *fdf, t_point point1, t_point point2);
void	_fdf_mlx_draw_line_gradient(t_fdf *fdf, t_point point1, t_point point2);
void	_fdf_display(t_fdf *fdf);

/* hook */
int		_fdf_exit(t_fdf *fdf);
int		_fdf_key_hook(int keycode, t_fdf *fdf);

/* utils */
int		_fdf_atoi_base(char *str, char *base);

#endif