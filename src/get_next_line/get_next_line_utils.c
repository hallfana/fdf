/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:27:56 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/10 01:02:16 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	_gnl_cleanup_fd(t_gnl *f)
{
	if (f->buf)
	{
		free(f->buf);
		f->buf = NULL;
	}
}
