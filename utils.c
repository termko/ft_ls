/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 19:40:17 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/18 16:09:26 by ydavis           ###   ########.fr       */
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

void	fill_fileaddr(t_cont *cont)
{
	t_fil	*tmp;
	int		i;

	check_malloc(cont->faddr = (t_fil**)malloc(sizeof(t_fil*) * (cont->num + 1)));
	tmp = cont->files;
	i = 0;
//	printf("%d\n", cont->num);
	while (tmp)
	{
//		printf("%d %s TMP = %p %s\n", i, cont->name, tmp, tmp->name);
		cont->faddr[i] = tmp;
		i++;
		tmp = tmp->next;
	}
	cont->faddr[i] = NULL;
}
