/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 19:38:05 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/23 03:30:30 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		fill_file(t_fil *file, char *name, struct stat stat)
{
	struct group	*grp;
	struct passwd	*tf;

	check_malloc(file->name = ft_strdup(name));
	if (lstat(file->name, &file->stat))
	{
		perror(file->name);
		return (-1);
	}
	file->group = NULL;
	file->owner = NULL;
	if ((grp = getgrgid(file->stat.st_gid)))
		check_malloc(file->group = ft_strdup(grp->gr_name));
	else
		perror(file->name);
	if ((tf = getpwuid(file->stat.st_uid)))
		check_malloc(file->owner = ft_strdup(tf->pw_name));
	else
		perror(file->name);
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
	{
		if (file == cont->files)
		{
			free_file(&(cont->files));
			cont->files = NULL;
		}
		tmp = cont->files;
		while (tmp->next != file)
			tmp = tmp->next;
		free_file(&(tmp->next));
		tmp->next = NULL;
	}
}

t_cont	*set_path(int ac, char **av, t_fl fl)
{
	t_cont		*cont;
	struct stat	st;
	int			i;
	char		*tmp;

	check_malloc(cont = (t_cont*)malloc(sizeof(t_cont)));
	cont->name = NULL;
	cont->files = NULL;
	cont->dirs = NULL;
	cont->from_av = 1;
	cont->is_root = 1;
	cont->fil_num = 0;
	cont->dir_num = 0;
	cont->mlen = 0;
	i = 0;
	while (i < ac)
	{
		if ((fl.l ? lstat(av[i], &st) : stat(av[i], &st)))
		{
			perror(av[i]);
			i++;
			continue ;
		}
		if (S_ISDIR(st.st_mode))
			create_dir(cont, av[i], fl, 2);
		else
		{
			put_file(cont, av[i], st);
			cont->fil_num++;
			cont->mlen = (cont->mlen > ft_strlen(av[i]) ? cont->mlen : ft_strlen(av[i]));
		}
		i++;
	}
	cont->mlen = in_which_inter(cont->mlen);
	cont->dir_num = i - cont->fil_num;
	cont->num = cont->fil_num;
	fill_fileaddr(cont);
	return (cont);
}
