/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 02:07:57 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/28 19:35:16 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int argc, char **argv)
{
	t_cont	*cont;
	t_fl	fl;

	g_ret = 0;
	fl = (t_fl){0, 0, 0, 0, 0, 0, 0, 0};
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
		exit(EXIT_FAILURE);
	sort_print(cont, fl, argc);
	return (g_ret);
}
