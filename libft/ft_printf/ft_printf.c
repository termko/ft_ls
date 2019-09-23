/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 17:37:45 by vellery-          #+#    #+#             */
/*   Updated: 2019/08/15 10:14:45 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		result(t_arg *arg)
{
	int ret;
	int i;

	i = 0;
	ret = arg->buf_len + arg->char_len + arg->full_len;
	write(1, arg->head, ret);
	if (arg->color)
		write(1, RES, 4);
	if (arg->head)
		ft_strdel(&arg->head);
	if (arg->format_head)
		free(arg->format_head);
	free(arg);
	return (ret);
}

void	save_this(t_arg *arg)
{
	char	*tmp;
	int		until;

	until = until_perc(arg->format);
	if (!arg->head)
	{
		arg->head = ft_strnew(until + 1);
		ft_strncpy(arg->head, arg->format, until);
		arg->buf = arg->head + until;
	}
	else
	{
		tmp = ft_strndup(arg->head, arg->full_len +
			arg->buf_len + arg->char_len);
		ft_strdel(&arg->head);
		arg->head = ft_strnjoin(tmp, arg->format,
						arg->full_len + arg->buf_len + arg->char_len, until);
		arg->buf = arg->head + arg->full_len + arg->buf_len
						+ arg->char_len + until;
		ft_strdel(&tmp);
	}
	arg->format += until;
	arg->full_len += until;
}

int		save_format(t_arg *arg, const char *format)
{
	if (!*format || !(arg->format = ft_strdup(format)))
	{
		free(arg);
		return (0);
	}
	arg->format_head = arg->format;
	arg->buf = NULL;
	arg->ptr_buf_save = NULL;
	arg->head = NULL;
	arg->length[0] = '\0';
	arg->length[1] = '\0';
	arg->length[2] = '\0';
	arg->char_len = 0;
	arg->full_len = 0;
	arg->buf_len = 0;
	arg->color = 0;
	arg->l = 0;
	return (1);
}

int		ft_printf_(va_list args, const char *format)
{
	t_arg	*arg;

	if (!(arg = (t_arg*)malloc(sizeof(t_arg))) || !save_format(arg, format))
		return (0);
	while (arg->format && *arg->format)
	{
		if (*arg->format == '{')
			set_color(arg);
		if (*arg->format == '%' && *(arg->format + 1) != '%')
			set_all_fields(args, arg);
		else if (*arg->format == '%' && *(arg->format + 1) == '%')
			save_perc(arg);
		else
			save_this(arg);
	}
	return (result(arg));
}

int		ft_printf(const char *format, ...)
{
	int		ret;
	va_list	args;

	ret = 0;
	va_start(args, format);
	ret = ft_printf_(args, format);
	va_end(args);
	return (ret);
}
