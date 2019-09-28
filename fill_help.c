/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 07:40:34 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/28 18:39:05 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	add_slash(t_fil *file, char *name)
{
	check_malloc(file->name = ft_strnew(ft_strlen(name) + 1));
	file->name = ft_strcat(file->name, name);
	file->name = ft_strcat(file->name, "/");
}

int		fill_check(t_cont *cont, t_fil *file, char *name, t_fl fl)
{
	file->full_path = set_fullname(cont->name, name);
	if (lstat(file->full_path, &file->stat))
	{
		free(file->full_path);
		g_ret = 1;
		return (1);
	}
	set_details(file);
	if (!file->group || !file->owner)
	{
		free(file->full_path);
		return (1);
	}
	file->is_dir = (is_file(file->full_path) ? 0 : 1);
	if (file->is_dir)
	{
		cont->dir_num++;
		if (fl.p)
			add_slash(file, name);
	}
	if (!file->name)
		check_malloc(file->name = ft_strdup(name));
	return (0);
}

void	check_head(t_fil **files, int count)
{
	t_fil	*tmp;
	int		i;

	if (!count)
		return ;
	tmp = *files;
	i = 0;
	while (i < count - 1)
	{
		i++;
		tmp = tmp->next;
	}
	if (tmp->next)
	{
		free(tmp->next);
		tmp->next = NULL;
	}
}
