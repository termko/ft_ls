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
	t_dirs	*path;
	t_fl	fl;

	fl = (t_fl){0, 0, 0, 0, 0, 0};
	init_fl(&argc, &argv, &fl);
//	print_args(argv, argc);
	first_sort(argv);
	path = argc == 0 ? create_dir("./", fl, 1) : set_path(argc, argv, fl);

//	print_args(argv, argc);
	sort_master(path, fl);
	if (fl.l)
		len_count(path);
	print_master(path, fl);
	// print_flags(&fl);
	return (0);
}
