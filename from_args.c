/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 19:38:05 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/23 07:39:45 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		fill_file(t_fil *file, char *name, struct stat stat)
{
	check_malloc(file->name = ft_strdup(name));
	if (lstat(file->name, &file->stat))
	{
		perror(file->name);
		return (-1);
	}
	fill_owngroup(file);
	if (!file->group || !file->owner)
		return (-1);
	if (S_ISDIR(stat.st_mode))
	{
		file->is_dir = 1;
		return (0);
	}
	file->is_dir = 0;
	check_malloc(file->full_path = ft_strdup(file->name));
	file->next = NULL;
	return (0);
}

void	put_file(t_cont *cont, char *name, struct stat stat)
{
	t_fil *file;
	t_fil *tmp;

	if (!cont->files)
	{
		check_malloc(cont->files = (t_fil*)malloc(sizeof(t_fil)));
		file = cont->files;
	}
	else
	{
		file = cont->files;
		while (file->next)
			file = file->next;
		check_malloc(file->next = (t_fil*)malloc(sizeof(t_fil)));
		file = file->next;
	}
	if (fill_file(file, name, stat))
		failed_fill(cont, file);
}

t_cont	*set_path(int ac, char **av, t_fl fl)
{
	t_cont		*cont;
	struct stat	st;
	int			i;
	char		*tmp;

	cont = init_cont();
	i = 0;
	while (i < ac)
	{
		if ((fl.l ? lstat(av[i], &st) : stat(av[i], &st)))
		{
			perror(av[i]);
			i++;
			continue ;
		}
		check_file(cont, st, fl, av[i]);
		i++;
	}
	cont->mlen = in_which_inter(cont->mlen);
	cont->dir_num = i - cont->fil_num;
	cont->num = cont->fil_num;
	fill_fileaddr(cont);
	return (cont);
}
