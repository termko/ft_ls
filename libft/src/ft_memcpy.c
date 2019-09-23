/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 03:45:22 by vellery-          #+#    #+#             */
/*   Updated: 2018/12/06 22:09:55 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*from;
	unsigned char	*to;

	if (n == 0)
		return (dst);
	i = 0;
	from = (unsigned char*)src;
	to = (unsigned char*)dst;
	while (i < n)
	{
		to[i] = from[i];
		i++;
	}
	return (dst);
}
