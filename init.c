/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 06:52:04 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/28 22:35:04 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		is_file(char *path)
{
	struct stat	path_stat;
	int			i;

	if ((i = lstat(path, &path_stat)))
	{
		just_perror(path);
		g_ret = 1;
		return (-1);
	}
	return (!S_ISDIR(path_stat.st_mode));
}

int		fill_opt(t_fl *fl, char *arg)
{
	char	*flags;
	int		i;

	flags = "lRartf1p";
	if (!fl || !arg)
		return (0);
	i = 0;
	while (arg[i])
	{
		if (!ft_strchr(flags, arg[i]) || (arg[0] == '-'
							&& arg[1] && arg[1] == '-'))
			illegal_opt(arg[i]);
		fill_flags(fl, arg[i]);
		i++;
	}
	return (1);
}

void	init_fl(int *ac, char ***av, t_fl *fl)
{
	int		count;
	int		i;

	if (!av || !*av)
		exit(1);
	count = 0;
	i = 1;
	while (i < *ac && (*av)[i][0] == '-')
	{
		if ((*av)[i][1])
			count += fill_opt(fl, (*av)[i] + 1);
		else
			break ;
		i++;
	}
	*ac -= count + 1;
	*av += i;
}

t_cont	*create_cont(char *path, t_fl fl, int is_root)
{
	t_cont	*cont;
	int		i;

	check_malloc(cont = (t_cont*)malloc(sizeof(t_cont)));
	check_malloc(cont->name = ft_strdup(path));
	cont->dirs = NULL;
	cont->files = NULL;
	cont->is_root = (is_root == 1 ? 1 : 0);
	cont->from_av = (is_root == 2 ? 1 : 0);
	cont->dir_num = 0;
	cont->fil_num = 0;
	cont->num = 0;
	i = fill_files_from_path(cont, fl);
	if (!cont->files && i < 0)
	{
		free(cont->name);
		free(cont);
		return (NULL);
	}
	fill_fileaddr(cont);
	return (cont);
}

void	create_dir(t_cont *cont, char *path, t_fl fl, int is_root)
{
	t_dirs *dir;
	t_dirs *tmp;

	check_malloc(dir = (t_dirs*)malloc(sizeof(t_dirs)));
	check_malloc(dir->name = ft_strdup(path));
	dir->cont = create_cont(path, fl, is_root);
	if (!(dir->cont))
	{
		free(dir->name);
		free(dir);
		return ;
	}
	dir->next = NULL;
	if (!cont->dirs)
		cont->dirs = dir;
	else
	{
		tmp = cont->dirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = dir;
	}
}
