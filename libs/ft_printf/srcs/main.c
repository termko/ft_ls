/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbreiten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 23:54:01 by dbreiten          #+#    #+#             */
/*   Updated: 2019/09/18 05:23:48 by dbreiten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include "../includes/ft_printf.h"

static int	error(t_buf *buf)
{
	clean_buf(buf);
	delete_buf(buf);
	return (-1);
}

static int	parse_one_data(t_buf *buf, char **format, va_list list)
{
	t_handle ht;

	(*format)++;
	ht.flags = parse_flags(format);
	ht.width = parse_width(format, list);
	ht.per = parse_per(format, list);
	ht.size = parse_size(format);
	return (parse_hndl_type(buf, &ht, format, list));
}

static int	parse_format(int fd, const char *format, va_list list)
{
	t_buf	*fd_buf;
	ssize_t	ret;

	fd_buf = create_buf(fd, 4096);
	if (fd_buf == NULL)
		return (-1);
	while (*format)
	{
		if (*format == '%')
		{
			if (parse_one_data(fd_buf, (char **)&format, list) == -1)
				return (error(fd_buf));
		}
		else
		{
			if (write_buf(fd_buf, (void*)format, 1, 1) == -1)
				return (error(fd_buf));
			format++;
		}
	}
	ret = clean_buf(fd_buf);
	delete_buf(fd_buf);
	return (ret);
}

int			ft_printf(const char *format, ...)
{
	va_list	list;
	int		res;

	va_start(list, format);
	res = parse_format(STDOUT_FILENO, format, list);
	va_end(list);
	return (res);
}

int			ft_fprintf(int fd, const char *format, ...)
{
	va_list	list;
	int		res;

	va_start(list, format);
	res = parse_format(fd, format, list);
	va_end(list);
	return (res);
}
