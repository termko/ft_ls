/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 07:25:27 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/23 07:38:38 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	check_file(t_cont *cont, struct stat st, t_fl fl, char *file)
{
	if (S_ISDIR(st.st_mode))
		create_dir(cont, file, fl, 2);
	else
	{
		put_file(cont, file, st);
		cont->fil_num++;
		cont->mlen = max(cont->mlen, ft_strlen(file));
	}
}

void	fill_owngroup(t_fil *file)
{
	struct group	*grp;
	struct passwd	*tf;

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
}

void	failed_fill(t_cont *cont, t_fil *file)
{
	t_fil *tmp;

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

t_cont	*init_cont(void)
{
	t_cont	*cont;

	check_malloc(cont = (t_cont*)malloc(sizeof(t_cont)));
	cont->name = NULL;
	cont->files = NULL;
	cont->dirs = NULL;
	cont->from_av = 1;
	cont->is_root = 1;
	cont->fil_num = 0;
	cont->dir_num = 0;
	cont->mlen = 0;
	return (cont);
}
