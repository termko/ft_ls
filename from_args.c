/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 19:38:05 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/09 09:28:55 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	fill_file(t_dirs *dir, t_fil *file, char *name, struct stat stat)
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

void	put_file(t_dirs *dir, char *name, struct stat stat)
{
	t_fil *file;

	file = dir->file;
	if (!dir->file)
	{
		check_malloc(dir->file = (t_fil*)malloc(sizeof(t_fil)));
		file = dir->file;
	}
	else
	{
		file = dir->file;
		while (file->next)
			file = file->next;
		check_malloc(file->next = (t_fil*)malloc(sizeof(t_fil)));
		file = file->next;
	}
	fill_file(dir, file, name, stat);
}

t_dirs	*set_path(int ac, char **av, t_fl fl)
{
	t_dirs		*dir;
	struct stat	stat;
	int			i;
	char		*tmp;
	t_dirs		*iter;

	check_malloc(dir = (t_dirs*)malloc(sizeof(t_dirs)));
	dir->name = NULL;
	dir->file = NULL;
	dir->from_av = 1;
	dir->fil_num = 0;
	dir->dir_num = 0;
	i = 0;
	iter = dir;
	while (i < ac)
	{
		if (lstat(av[i], &stat))
		{
			printf("ls: %s: No such file or directory\n", av[i]);
			i++;
			continue ;
		}
		if (S_ISREG(stat.st_mode))
		{
			put_file(dir, av[i], stat);
			dir->fil_num++;
		}
		else if (S_ISDIR(stat.st_mode))
		{
			tmp = ft_strnew(ft_strlen(av[i]) + 2);
			tmp = ft_strcat(tmp, av[i]);
			tmp = ft_strcat(tmp, "/");
			iter->next = create_dir(tmp, fl, 0);
			iter = iter->next;
			free(tmp);
		}
		i++;
	}
	dir->num = dir->dir_num + dir->fil_num;
	fill_fileaddr(dir);
	return (dir);
}
