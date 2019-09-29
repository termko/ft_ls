/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbreiten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 03:18:10 by dbreiten          #+#    #+#             */
/*   Updated: 2018/12/02 23:15:29 by dbreiten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_ndig(long a)
{
	int count;

	count = 0;
	if (!a)
		return (1);
	while (a)
	{
		count++;
		a = a / 10;
	}
	return (count);
}

int			ft_atoi(const char *nptr)
{
	long		res;
	int			s;
	const char	*tmp;

	res = 0;
	s = 1;
	while (*nptr == ' ' || (*nptr <= 0xD && *nptr >= 0x9))
		nptr++;
	if (*nptr == '-' && nptr++)
		s = -1;
	else if (*nptr == '+')
		nptr++;
	while (*nptr == 0x30)
		nptr++;
	tmp = nptr;
	while (*nptr >= 0x30 && *nptr <= 0x39)
		res = res * 10 + (*nptr++ - 0x30);
	res = s * (res - 1) + s;
	if ((res * s < 0 || (nptr - tmp) != ft_ndig(res)) && (nptr - tmp) != 0)
	{
		if (s == -1)
			return (0);
		return (-1);
	}
	return (res);
}
