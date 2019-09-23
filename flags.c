/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 07:20:36 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/23 07:23:50 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	fill_flags(t_fl *fl, char c)
{
	if (c == 'l' || c == '1')
	{
		fl->l = (c == 'l' ? 1 : 0);
		fl->one = (c == '1' ? 1 : 0);
	}
	fl->up_r = (c == 'R' ? 1 : fl->up_r);
	fl->a = (c == 'a' ? 1 : fl->a);
	fl->r = (c == 'r' ? 1 : fl->r);
	fl->t = (c == 't' ? 1 : fl->t);
	if (c == 'f')
	{
		fl->f = 1;
		fl->a = 1;
	}
	fl->p = (c == 'p' ? 1 : fl->p);
}
