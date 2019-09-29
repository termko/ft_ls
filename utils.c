/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 19:40:17 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/29 16:35:12 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	check_malloc(void *addr)
{
	if (!addr)
		error_exit("Unexpected error with malloc! Exiting...\n");
}

void	error_exit(char *err)
{
	write(2, err, ft_strlen(err));
	exit(1);
}

void	fill_fileaddr(t_cont *cont)
{
	t_fil	*tmp;
	int		i;

	check_malloc(cont->faddr = (t_fil**)malloc(sizeof(t_fil*) *
				(cont->num + 1)));
	tmp = cont->files;
	i = 0;
	while (tmp)
	{
		if (tmp->is_dir && cont->is_root && cont->from_av)
		{
			tmp = tmp->next;
			continue ;
		}
		cont->faddr[i] = tmp;
		i++;
		tmp = tmp->next;
	}
	cont->faddr[i] = NULL;
}

long	ft_labs(long a)
{
	return ((a > 0 ? a : -a));
}

int		max(int a, int b)
{
	return (a > b ? a : b);
}
