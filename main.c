/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 02:07:57 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/23 05:22:05 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		sort_print(t_cont *cont, t_fl fl, int ac)
{
	static int	flag = 0;
	int		i;
	t_dirs	*dir;

	sort_master(cont, fl);
	if (fl.l)
		set_max_len(cont);
	print_master(cont, fl, ac);
	if (fl.up_r && cont->dir_num)
	{
		i = 0;
		while (cont->faddr[i])
		{
			if (cont->faddr[i]->is_dir)
			{
				if (cont->faddr[i]->name &&
						ft_strcmp(cont->faddr[i]->name, ".") &&
						ft_strcmp(cont->faddr[i]->name, ".."))
					create_dir(cont, cont->faddr[i]->full_path, fl, 0);
			}
			i++;
		}
	}
	if (cont->dirs)
	{
		if (!cont->name && cont->files)
			printf("\n");
		else if (cont->name && !ft_strcmp(cont->name, "."))
			printf("\n");
		else if (flag)
			printf("\n");
	}
	flag = 1;
	dir = cont->dirs;
	while (dir)
	{
		sort_print(dir->cont, fl, ac);
		dir = dir->next;
		if (dir)
			printf("\n");
	}
	free_cont(&cont);
}

int		main(int argc, char **argv)
{
	t_cont	*cont;
	t_fl	fl;

	fl = (t_fl){0, 0, 0, 0, 0, 0, 0};
	init_fl(&argc, &argv, &fl);
	if (argc)
	{
		if (!fl.f)
			first_sort(argv);
		cont = set_path(argc, argv, fl);
	}
	else
		cont = create_cont(".", fl, 1);
	if (!cont)
		exit(1);
	sort_print(cont, fl, argc);
	return (0);
}
