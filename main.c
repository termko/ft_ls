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

int		main(int argc, char **argv)
{
	t_cont	*cont;
	t_fl	fl;

	fl = (t_fl){0, 0, 0, 0, 0, 0};
	init_fl(&argc, &argv, &fl);
	first_sort(argv);
	cont = (argc == 0 ? create_cont("./", fl, 1) : set_path(argc, argv, fl));

	sort_master(cont, fl);
	if (fl.l)
		set_max_len(cont);
	print_master(cont, fl);
	return (0);
}
