/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_permissions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 06:03:17 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/23 06:07:18 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	first_perm(char *ret, mode_t mode)
{
	int		val;

	ret[0] = (mode & S_IRUSR ? 'r' : '-');
	ret[1] = (mode & S_IWUSR ? 'w' : '-');
	val = mode & (S_IXUSR | S_ISUID);
	if (val == 0 || val == S_ISUID)
		ret[2] = (val == 0 ? '-' : 'x');
	else if (val == S_ISUID || val == (S_IXUSR | S_ISUID))
		ret[2] = (val == S_ISUID ? 'S' : 's');
}
