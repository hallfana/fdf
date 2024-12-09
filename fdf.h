/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 20:05:57 by samberna          #+#    #+#             */
/*   Updated: 2024/12/09 01:11:36 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/* IMPORTED FROM github.com/tcarlier42/get_next_line */
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct s_gnl
{
	char	*buf;
	ssize_t	pos;
	int		tab;
	int		c;
}	t_gnl;

char	*get_next_line(int fd);
char	*ft_strdup(const char *s);
void	ft_init(t_gnl *f);
size_t	ft_strlen(const char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
void	cleanup_fd(t_gnl *f);


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

#endif