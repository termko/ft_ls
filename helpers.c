/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 06:53:18 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/23 07:01:05 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	set_len(int *cont, char *str)
{
	int		len;

	if (!str)
		return ;
	len = ft_strlen(str);
	*cont = max(len, *cont);
}

void	set_max_len(t_cont *cont)
{
	t_fil	*head;
	char	*tmp;

	head = cont->files;
	cont->total = 0;
	cont->link_len = 0;
	cont->own_len = 0;
	cont->grp_len = 0;
	cont->size_len = 0;
	while (head)
	{
		cont->total += head->stat.st_blocks;
		set_len(&(cont->own_len), head->owner);
		set_len(&(cont->grp_len), head->group);
		tmp = ft_intmaxtoa(head->stat.st_nlink, 10);
		set_len(&(cont->link_len), tmp);
		free(tmp);
		tmp = ft_intmaxtoa(head->stat.st_size, 10);
		set_len(&(cont->size_len), tmp);
		free(tmp);
		head = head->next;
	}
}
