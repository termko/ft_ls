/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 02:07:57 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/23 07:09:22 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
