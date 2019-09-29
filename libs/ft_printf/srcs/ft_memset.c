/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbreiten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:51:36 by dbreiten          #+#    #+#             */
/*   Updated: 2018/12/03 00:11:11 by dbreiten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *ptr, int value, size_t num)
{
	void *st;

	st = ptr;
	while (num--)
		*(unsigned char*)ptr++ = (unsigned char)value;
	return (st);
}
