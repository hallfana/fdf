/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:27:56 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/09 01:11:03 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* get_next_line_utils.c */
/* get_next_line_utils.c */
#include "fdf.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	ft_init(t_gnl *f)
{
	if (!(*f).buf)
	{
		(*f).buf = ft_strdup("");
		if (!(*f).buf)
			return ;
		(*f).tab = 0;
	}
}

void	cleanup_fd(t_gnl *f)
{
	if (f->buf)
	{
		free(f->buf);
		f->buf = NULL;
	}
}
