/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 06:25:38 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/23 06:31:28 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		sort_standart(t_fil *a, t_fil *b)
{
	return (ft_strcmp(a->name, b->name));
}

int		sort_rev(t_fil *a, t_fil *b)
{
	return (ft_strcmp(b->name, a->name));
}

int		sort_time(t_fil *a, t_fil *b)
{
	return (b->stat.st_mtime - a->stat.st_mtime);
}

int		sort_timerev(t_fil *a, t_fil *b)
{
	return (a->stat.st_mtime - b->stat.st_mtime);
}
