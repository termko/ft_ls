/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 20:28:08 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/23 07:01:54 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	re_cmp(char **lower, char **upper)
{
	char *tmp;

	if (lower != upper)
	{
		tmp = *lower;
		*lower = *upper;
		*upper = tmp;
	}
}

void	first_sort(char **arg)
{
	int i;
	int j;

	i = 0;
	while (arg[i])
	{
		j = i;
		while (arg[j])
		{
			if (ft_strcmp(arg[i], arg[j]) > 0)
				re_cmp(&arg[i], &arg[j]);
			j++;
		}
		i++;
	}
}

void	change_faddr(t_fil **a, t_fil **b, int r, int res)
{
	t_fil	*tmp;
	int		flag;

	flag = 0;
	if (res)
		flag = 1;
	else if (!res && r)
	{
		if (sort_rev(*a, *b) < 0)
			flag = 1;
	}
	else if (!res && !r)
	{
		if (sort_standart(*a, *b) < 0)
			flag = 1;
	}
	if (flag)
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
}

void	cycle_sort(t_cont *cont, int (*sort)(t_fil *a, t_fil *b), t_fl fl)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	while (cont->faddr[i])
	{
		j = i;
		while (cont->faddr[j])
		{
			if (cont->faddr[i]->name && cont->faddr[j]->name)
			{
				if ((res = sort(cont->faddr[i], cont->faddr[j])) > 0)
					change_faddr(&cont->faddr[i], &cont->faddr[j], fl.r, res);
			}
			j++;
		}
		i++;
	}
}

void	sort_master(t_cont *cont, t_fl fl)
{
	int		(*sort)(t_fil *a, t_fil *b);
	int		i;
	int		j;
	int		res;

	if (fl.f)
		return ;
	if (fl.r)
	{
		if (fl.t)
			sort = sort_timerev;
		else
			sort = sort_rev;
	}
	else
	{
		if (fl.t)
			sort = sort_time;
		else
			sort = sort_standart;
	}
	cycle_sort(cont, sort, fl);
}
