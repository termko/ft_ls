/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbreiten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 00:02:30 by dbreiten          #+#    #+#             */
/*   Updated: 2019/09/18 05:19:13 by dbreiten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MINCHNK 4096

t_buf	*create_buf(int fd, size_t size)
{
	t_buf	*new;

	new = malloc(sizeof(t_buf));
	if (new == NULL)
		return (NULL);
	new->data = malloc(size);
	if (new->data == NULL)
	{
		free(new);
		return (NULL);
	}
	new->fd = fd;
	new->all_size = size;
	new->curr_size = 0;
	return (new);
}

void	delete_buf(t_buf *buf)
{
	free(buf->data);
	free(buf);
}

void	*ft_realloc(void *src, size_t curr_size, size_t new_size)
{
	void	*new;

	new = malloc(new_size);
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, src, curr_size);
	free(src);
	return (new);
}

ssize_t	write_buf(t_buf *buf, void *data, size_t size, size_t num)
{
	size_t	i;

	while (buf->all_size - buf->curr_size < size * num)
	{
		buf->data = ft_realloc(buf->data,
								buf->curr_size,
								buf->all_size + MINCHNK);
		if (buf->data == NULL)
			return (-1);
		buf->all_size += MINCHNK;
	}
	i = 0;
	while (i < num)
	{
		ft_memcpy(buf->data + buf->curr_size, data, size);
		buf->curr_size += size;
		i++;
	}
	return (size * num);
}

ssize_t	clean_buf(t_buf *buf)
{
	size_t	ret;

	ret = write(buf->fd, buf->data, buf->curr_size);
	buf->curr_size = 0;
	return (ret);
}
