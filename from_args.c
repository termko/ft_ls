/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 19:38:05 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/29 22:28:30 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		fill_dir(t_fil *file)
{
	file->is_dir = 1;
	check_malloc(file->full_path = ft_strdup(file->name));
	file->group = NULL;
	file->owner = NULL;
	file->next = NULL;
	return (0);
}

int		fill_file(t_fil *file, char *name, struct stat stat, int is_dir)
{
	check_malloc(file->name = ft_strdup(name));
	if (is_dir)
	{
		return (fill_dir(file));
	}
	if (lstat(file->name, &file->stat))
	{
		g_ret = 1;
		just_perror(file->name);
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

void	put_file(t_cont *cont, char *name, struct stat stat, int is_dir)
{
	t_fil *file;

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
	if (fill_file(file, name, stat, is_dir))
		failed_fill(cont, file);
}

void	check_file(t_cont *cont, struct stat st, t_fl fl, char *file)
{
	(void)fl;
	if (S_ISDIR(st.st_mode))
		put_file(cont, file, st, 1);
	else
	{
		put_file(cont, file, st, 0);
		cont->fil_num++;
		cont->mlen = max(cont->mlen, ft_strlen(file));
	}
}

t_cont	*set_path(int ac, char **av, t_fl fl)
{
	t_cont		*cont;
	struct stat	st;
	int			i;

	cont = init_cont();
	i = 0;
	while (i < ac)
	{
		if ((fl.l ? lstat(av[i], &st) : stat(av[i], &st)))
		{
			g_ret = 1;
			just_perror(av[i]);
			i++;
			continue ;
		}
		check_file(cont, st, fl, av[i]);
		i++;
	}
	cont->mlen = in_which_inter(cont->mlen);
	cont->dir_num = i - cont->fil_num;
	cont->num = cont->fil_num;
	set_max_len(cont);
	fill_fileaddr(cont);
	return (cont);
}
