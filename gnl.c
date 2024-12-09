/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:27:54 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/09 01:40:51 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* get_next_line.c */
#include "fdf.h"

static char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

static char	*ft_extract_line(char **str, t_gnl *f)
{
	char	*line;
	char	*tmp;
	int		i;

	i = 0;
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	if ((*str)[i] == '\n')
		i++;
	line = gnl_ft_substr(*str, 0, i);
	tmp = gnl_ft_substr(*str, i, gnl_ft_strlen(*str) - i);
	free(*str);
	if (!tmp)
	{
		free(line);
		*str = NULL;
		return (NULL);
	}
	*str = tmp;
	if ((*str) == 0)
		free(f);
	return (line);
}

static char	*ft_realloc(char *old, size_t olds, size_t news)
{
	char	*new;
	int		i;

	if (news == 0)
		return (old);
	new = malloc(olds + news + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (old[i])
	{
		new[i] = old[i];
		i++;
	}
	new[i] = '\0';
	free(old);
	return (new);
}

static void	ft_find_new(t_gnl *f, ssize_t *bytes, int fd)
{
	int	len;

	len = gnl_ft_strlen((*f).buf);
	while (!ft_strchr((*f).buf, '\n') && *bytes > 0)
	{
		(*f).buf = ft_realloc((*f).buf, gnl_ft_strlen((*f).buf), BUFFER_SIZE);
		if (!(*f).buf)
			return ;
		*bytes = read(fd, (*f).buf + gnl_ft_strlen((*f).buf), BUFFER_SIZE);
		if (*bytes > 0)
		{
			(*f).buf[*bytes + len] = '\0';
			len += *bytes;
			(*f).tab += *bytes;
		}
		else if (*bytes < 0)
		{
			gnl_cleanup_fd(f);
			return ;
		}
	}
}

char	*get_next_line(int fd)
{
	static t_gnl	f[1024];
	char			*line;
	ssize_t			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
	{
		return (NULL);
	}
	gnl_ft_init(&f[fd]);
	line = NULL;
	bytes = 1;
	ft_find_new(&f[fd], &bytes, fd);
	if (f[fd].buf && *f[fd].buf)
	{
		line = ft_extract_line(&f[fd].buf, &f[fd]);
		if (!line)
			return (NULL);
		return (line);
	}
	if (bytes <= 0 || (!f[fd].buf || !*f[fd].buf))
		gnl_cleanup_fd(&f[fd]);
	return (line);
}

// int	main(void)
// {
// 	int fd1;
// 	char *line;

// 	fd1 = open("test.txt", O_RDONLY);
// 	int fd2 = open("test2.txt", O_RDONLY);
// 	if (fd1 == -1 || fd2 == -1)
// 		return (0);
// 	line = get_next_line(21);
// 	printf("%s", line);
// 	line = get_next_line(fd1);
// 	printf("%s", line);
// 	close(fd1);
// 	close(fd2);
// 	return (0);
// }
