/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallfana <hallfana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 20:05:57 by samberna          #+#    #+#             */
/*   Updated: 2024/12/09 16:47:37 by hallfana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/* IMPORTED FROM github.com/tcarlier42/get_next_line */
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "./mlx_linux/mlx.h"
# include "./libft/libft.h"
# include <math.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# define WINX 900
# define WINY 900

typedef struct s_gnl
{
	char	*buf;
	ssize_t	pos;
	int		tab;
	int		c;
}	t_gnl;

char	*get_next_line(int fd);
char	*gnl_ft_strdup(const char *s);
void	gnl_ft_init(t_gnl *f);
size_t	gnl_ft_strlen(const char *s);
char	*gnl_ft_substr(char *s, unsigned int start, size_t len);
void	gnl_cleanup_fd(t_gnl *f);

// SHITTY FDF HERE //
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_fdf {
	void	*mlx;
	void	*mlx_win;
}				t_fdf;

typedef struct s_point {
	int x;
	int y;
	int z;
	int color;
}				t_point;

typedef struct s_tab {
	t_point **tab;
	int		width;
	int		height;
}				t_tab;

int		keyboardHandler(int code, void *param);
void	my_mlx_line_put(t_data img, int x1, int y1, int x2, int y2);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif