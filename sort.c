/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 20:28:08 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/09 08:26:51 by ydavis           ###   ########.fr       */
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

/*
void	first_sort(char **arg, int end)
{
	int		low;
	int		upp;
	char	*piv;

	if (!arg || !*arg || end <= 1)
		return ;
	piv = arg[end / 2];
	low = 0;
	upp = end - 1;
	while (low < upp)
	{	
		while (ft_strcmp(arg[low], piv) < 0)
			low++;
		while (ft_strcmp(arg[upp], piv) > 0)
			upp--;
		if (low < upp)
		{	
			re_cmp(&arg[low], &arg[upp]);
			low++;
			upp--;
		}
	}
	first_sort(arg, low);
	first_sort(&arg[low], end - low);
}
*/

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
	if (!res && r)
	{
		if (sort_rev(*a, *b) < 0)
			flag = 1;
	}
	else if (!res && !r)
	{
		if (sort_standart(*a, *b) < 0)
			flag = 1;
	}
	else
		flag = 1;
	if (flag)
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
}

// TODO: NO CASE CMP

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

void	sort_master(t_dirs *dir, t_fl fl)
{
	int		(*sort)(t_fil *a, t_fil *b);
	int		i;
	int		j;
	int		res;

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
			return ;
	}
	i = 0;
	while (i < dir->num)
	{
		j = 0;
		while (j < dir->num)
		{
			if ((res = sort(dir->faddr[i], dir->faddr[j])) <= 0)
				change_faddr(&dir->faddr[i], &dir->faddr[j], fl.r, res);
			j++;
		}
		i++;
	}
}
