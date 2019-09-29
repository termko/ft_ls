/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbreiten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 03:14:03 by dbreiten          #+#    #+#             */
/*   Updated: 2018/11/23 03:27:07 by dbreiten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_strncmp(const char *s1, const char *s2, size_t len)
{
	while (*s1 && len && *s1 == *s2)
	{
		s1++;
		s2++;
		len--;
	}
	if (!len)
		return (0);
	return (*(unsigned char*)s1 - *(unsigned char *)s2);
}
