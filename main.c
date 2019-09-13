/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 02:07:57 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/09 07:34:12 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		sort_print(t_cont *cont, t_fl fl)
{
	int i;

	sort_master(cont, fl);
	if (fl.l)
		set_max_len(cont);
	print_master(cont, fl);
	if (fl.up_r && cont->dir_num)
	{
		i = 0;
		while (cont->faddr[i])
		{
			if (S_ISDIR(cont->faddr[i]->stat.st_mode))
				create_dir(cont, cont->faddr[i]->full_path, fl, 0);
			i++;
		}
	}
	while (cont->dirs)
	{
		sort_print(cont->dirs->cont, fl);
		cont->dirs = cont->dirs->next;
	}
}

int		main(int argc, char **argv)
{
	t_cont	*cont;
	t_fl	fl;

	fl = (t_fl){0, 0, 0, 0, 0, 0, 0};
	init_fl(&argc, &argv, &fl);
	if (argc)
	{
		first_sort(argv);
		cont = set_path(argc, argv, fl);
	}
	else
		cont = create_cont("./", fl, 1);
	sort_print(cont, fl);
	return (0);
}
