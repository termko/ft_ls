/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 19:40:17 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/08 23:40:39 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	check_malloc(void *addr)
{
	if (!addr)
	{
		ft_putendl("Unexpected error with malloc! Exiting...");
		exit(1);
	}
}

void	fill_fileaddr(t_dirs *dir)
{
	t_fil	*tmp;
	int		i;

	check_malloc(dir->faddr = (t_fil**)malloc(sizeof(t_fil*) * (dir->dir_num + dir->fil_num + 1)));
	tmp = dir->file;
	i = 0;
	while (tmp)
	{
		dir->faddr[i] = tmp;
		i++;
		tmp = tmp->next;
	}
	dir->faddr[i] = NULL;
	i = 0;
}
