/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 07:02:48 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/29 16:43:21 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_cont	*find_cont(t_cont *cont)
{
	t_dirs *tmp;

	tmp = cont->dirs;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp->cont);
}

void	next_dir(t_cont *cont)
{
	static int	flag = 0;

		if (!cont->name && cont->fil_num)
		{
			ft_printf("\n");
		}
		else if (cont->name && !ft_strcmp(cont->name, "."))
		{
			ft_printf("\n");
		}
		else if (flag)
		{
			ft_printf("\n");
		}
	flag = 1;
}

t_dirs	*find_dir(t_cont *cont, char *path)
{
	t_dirs *ret;

	ret = cont->dirs;
	if (!ret)
		return (ret);
	while (ret->next)
	{
		if (!ft_strcmp(ret->name, path))
			return (ret);
		ret = ret->next;
	}
	return ((ft_strcmp(ret->name, path) ? NULL : ret));
}

void	recursion_normal(t_cont *cont, t_fl fl, int ac)
{
	int			i;
	t_dirs		*dir;

	i = 0;
	while (cont->faddr[i])
	{
		if (cont->faddr[i]->is_dir)
		{
			if (cont->faddr[i]->name &&
					ft_strcmp(cont->faddr[i]->name, ".") &&
					ft_strcmp(cont->faddr[i]->name, ".."))
			{
				next_dir(cont);
				ft_printf("%s:\n", cont->faddr[i]->full_path);
				create_dir(cont, cont->faddr[i]->full_path, fl, 0);
				if (!(dir = find_dir(cont, cont->faddr[i]->full_path)))
				{
					i++;
					continue ;
				}
				sort_print(dir->cont, fl, ac);
			}
		}
		i++;
	}
}

void	recursion_av(t_cont *cont, t_fl fl, int ac)
{
	t_fil	*file;
	t_dirs	*dir;

	file = cont->files;
	while (file)
	{
		if (file->is_dir)
		{
			next_dir(cont);
			if (cont->fil_num || cont->dir_num > 1)
				ft_printf("%s:\n", file->full_path);
			create_dir(cont, file->full_path, fl, 0);
			if (!(dir = find_dir(cont, file->full_path)))
			{
				file = file->next;
				continue ;
			}
			sort_print(dir->cont, fl, ac);
		}
		file = file->next;
	}
}

void	sort_print(t_cont *cont, t_fl fl, int ac)
{
	t_dirs		*dir;

	sort_master(cont, fl);
	if (fl.l)
		set_max_len(cont);
	print_master(cont, fl, ac);
	if (fl.up_r && cont->dir_num && !cont->from_av)
	{
		recursion_normal(cont, fl, ac);
	}
	else if (cont->dir_num && cont->from_av && cont->is_root)
	{
		recursion_av(cont, fl, ac);
	}
	//next_dir(cont, flag);
/*
	dir = cont->dirs;
	while (dir)
	{
		sort_print(dir->cont, fl, ac);
		dir = dir->next;
		if (dir)
			ft_printf("\n");
	}
	*/
	(void)dir;
//	free_cont(&cont);
}
