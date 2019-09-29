/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbreiten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 02:14:09 by dbreiten          #+#    #+#             */
/*   Updated: 2019/09/18 05:22:55 by dbreiten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "../includes/ft_printf.h"

uintmax_t		uabs(intmax_t n)
{
	if (n < 0)
		return (-(uintmax_t)n);
	return ((uintmax_t)n);
}

static size_t	len_nb(intmax_t nb)
{
	int ret;

	if (!nb)
		return (1);
	ret = 0;
	while (nb)
	{
		ret++;
		nb /= 10;
	}
	return (ret);
}

static void		set_arr_n(intmax_t n, char *str)
{
	if (n >= 10)
		set_arr_n(n / 10, str - 1);
	*str = '0' + (n % 10);
}

char			*ft_fitoa(intmax_t nb, int perm, int show_sign)
{
	char	*res;
	size_t	len;

	if (nb < 0)
	{
		show_sign = -1;
		nb = uabs(nb);
	}
	len = len_nb(nb);
	if ((int)len < perm)
		len = (size_t)perm;
	len += (show_sign != 0);
	if (!(res = (char*)malloc(len + 1)))
		return (NULL);
	ft_memset(res, '0', len);
	res[len] = 0;
	set_arr_n(nb, res + len - 1);
	if (show_sign == 1)
		*res = '+';
	else if (show_sign == 2)
		*res = ' ';
	else if (show_sign == -1)
		*res = '-';
	return (res);
}
