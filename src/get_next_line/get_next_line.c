/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:27:54 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/12 18:24:14 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static int	fill_buffer(char **buf, int fd)
{
	int		is_eof;

	is_eof = 0;
	*buf = (char *) malloc(_GNL_BUFFER_SIZE * sizeof(char) + 1);
	if (*buf == NULL)
		return (0);
	is_eof = read(fd, *buf, _GNL_BUFFER_SIZE);
	if (is_eof < 0 || is_eof == 0)
	{
		free(*buf);
		return (is_eof);
	}
	(*buf)[is_eof] = '\0';
	return (is_eof);
}

static char	*reduce_tmp(char *str, int start)
{
	char	*new_tmp;
	int		i;

	if (gnl_strlen(&str[start], '\0') == 0)
	{
		free(str);
		return (NULL);
	}
	new_tmp = (char *) malloc((gnl_strlen(&str[start], '\0') + 1)
			* sizeof(char));
	if (new_tmp == NULL)
		return (NULL);
	i = 0;
	while (str[start] != '\0')
	{
		new_tmp[i] = str[start];
		start++;
		i++;
	}
	new_tmp[i] = '\0';
	free(str);
	return (new_tmp);
}

static int	read_new_line(char **tmp, int fd)
{
	char	*buf;
	int		is_eof;

	is_eof = -100;
	while (line_counter(*tmp) == 0 && is_eof != 0)
	{
		if (is_eof < _GNL_BUFFER_SIZE && is_eof != -100)
			break ;
		is_eof = fill_buffer(&buf, fd);
		if (is_eof == -1)
		{
			free (*tmp);
			*tmp = NULL;
			return (-1);
		}
		if (is_eof != 0)
			*tmp = gnl_strjoin(*tmp, buf);
	}
	return (is_eof);
}

static char	*get_new_line_from_tmp(char **tmp)
{
	char	*new_line;

	new_line = gnl_strdup(*tmp, '\n');
	*tmp = reduce_tmp(*tmp, gnl_strlen(*tmp, '\n') + 0);
	return (new_line);
}

char	*_gnl_get_next_line(int fd)
{
	char		*tmp;
	char		*new_line;
	int			is_eof;
	static char	*fd_tmp_storage[8192];	

	tmp = fd_tmp_storage[fd];
	new_line = NULL;
	if (line_counter(tmp) != 0)
		new_line = get_new_line_from_tmp(&tmp);
	else
	{
		is_eof = read_new_line(&tmp, fd);
		if (is_eof == -1)
		{
			fd_tmp_storage[fd] = tmp;
			return (NULL);
		}
	}
	if (new_line == NULL && ((is_eof == 0 && gnl_strlen(tmp, '\0') != 0)
			|| is_eof != 0))
		new_line = get_new_line_from_tmp(&tmp);
	fd_tmp_storage[fd] = tmp;
	return (new_line);
}

