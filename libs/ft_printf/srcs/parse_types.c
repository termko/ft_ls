/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbreiten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 04:21:10 by dbreiten          #+#    #+#             */
/*   Updated: 2019/09/18 05:04:58 by dbreiten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static const char *g_types = "douxXsc%";

static ssize_t	parse_hndl_type_d(t_buf *buf, t_handle *hndl, va_list list)
{
	if (hndl->size == LLPRE)
		return (parse_hndl_nb(buf, hndl, va_arg(list, long long)));
	if (hndl->size == LPRE)
		return (parse_hndl_nb(buf, hndl, va_arg(list, long)));
	if (hndl->size == HHPRE)
		return (parse_hndl_nb(buf, hndl, (char)va_arg(list, int)));
	if (hndl->size == HPRE)
		return (parse_hndl_nb(buf, hndl, (short)va_arg(list, int)));
	if (hndl->size == JPRE)
		return (parse_hndl_nb(buf, hndl, va_arg(list, intmax_t)));
	return (parse_hndl_nb(buf, hndl, va_arg(list, int)));
}

static ssize_t	parse_hndl_type_u(t_buf *buf, t_handle *hndl, va_list list)
{
	if (hndl->size == LLPRE)
		return (parse_hndl_unb(buf, hndl, va_arg(list, unsigned long long)));
	if (hndl->size == LPRE)
		return (parse_hndl_unb(buf, hndl, va_arg(list, unsigned long)));
	if (hndl->size == HHPRE)
		return (parse_hndl_unb(buf, hndl, (unsigned char)va_arg(list, int)));
	if (hndl->size == HPRE)
		return (parse_hndl_unb(buf, hndl, (unsigned short)va_arg(list, int)));
	if (hndl->size == JPRE)
		return (parse_hndl_unb(buf, hndl, va_arg(list, uintmax_t)));
	if (hndl->size == ZPRE)
		return (parse_hndl_unb(buf, hndl, va_arg(list, size_t)));
	return (parse_hndl_unb(buf, hndl, va_arg(list, unsigned int)));
}

static ssize_t	parse_unsigned_types(
t_buf *buf,
t_handle *hndl,
va_list list,
char t)
{
	if (t == 'o')
		hndl->base = OCTAL;
	else if (t == 'x')
		hndl->base = HEXL;
	else if (t == 'X')
		hndl->base = HEXU;
	else
		hndl->base = DEC;
	return (parse_hndl_type_u(buf, hndl, list));
}

ssize_t			parse_hndl_type(
t_buf *buf,
t_handle *hndl,
char **format,
va_list list)
{
	int	ret;

	ret = 0;
	while (**format && !ft_strchr(g_types, **format))
		(*format)++;
	if (ft_strchr("ouxX", **format))
		ret = (parse_unsigned_types(buf, hndl, list, **format));
	if (**format == 'd')
		ret = parse_hndl_type_d(buf, hndl, list);
	if (**format == 's')
		ret = parse_hndl_str(buf, hndl, va_arg(list, const char *));
	if (**format == 'c')
		ret = parse_hndl_sym(buf, hndl, (char)va_arg(list, int));
	if (**format == '%')
		ret = parse_hndl_sym(buf, hndl, '%');
	(*format)++;
	return (ret);
}
