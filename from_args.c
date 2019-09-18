/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 19:38:05 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/18 15:41:36 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	fill_file(t_fil *file, char *name, struct stat stat)
{
	struct group	*grp;
	struct passwd	*tf;

	file->name = ft_strdup(name);
	lstat(file->name, &file->stat);
	if (S_ISDIR(stat.st_mode))
	{
		file->is_dir = 1;
		return ;
	}
	file->is_dir = 0;
	grp = getgrgid(file->stat.st_gid);
	file->group = ft_strdup(grp->gr_name);
	tf = getpwuid(file->stat.st_uid);
	file->owner = ft_strdup(tf->pw_name);
	file->full_path = file->name;
	file->next = NULL;
}

void	put_file(t_cont *cont, char *name, struct stat stat)
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
	fill_file(file, name, stat);
}

t_cont	*set_path(int ac, char **av, t_fl fl)
{
	t_cont		*cont;
	struct stat	stat;
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
		if (lstat(av[i], &stat))
		{
			printf("ls: %s: No such file or directory\n", av[i]); // TODO: ERRNO STRERR
			i++;
			continue ;
		}
		if (S_ISDIR(stat.st_mode))
			create_dir(cont, av[i], fl, 0);
		else
		{
			put_file(cont, av[i], stat);
			cont->fil_num++;
			cont->mlen = (cont->mlen > ft_strlen(av[i]) ? cont->mlen : ft_strlen(av[i]));
		}
		i++;
	}
	cont->dir_num = i - cont->fil_num;
	cont->num = i;
	fill_fileaddr(cont);
	return (cont);
}
