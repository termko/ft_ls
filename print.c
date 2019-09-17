/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 02:08:07 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/09 09:26:48 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_type(mode_t mode)
{
	int	val;

	val = mode & S_IFMT;
	if (val == S_IFBLK)
		printf("b");
	else if (val == S_IFCHR)
		printf("c");
	else if (val == S_IFLNK)
		printf("l");
	else if (val == S_IFIFO)
		printf("p");
	else if (val == S_IFDIR)
		printf("d");
	else if (val == S_IFSOCK)
		printf("s");
	else if (val == S_IFREG)
		printf("-");
	else
		printf("?");
}

void	print_permissions(mode_t mode)
{
	int		val;
	char	ret[10];

	ret[0] = (mode & S_IRUSR ? 'r' : '-');
	ret[1] = (mode & S_IWUSR ? 'w' : '-');
	val = mode & (S_IXUSR | S_ISUID);
	if (val == 0 || val == S_IXUSR)
		ret[2] = (val == 0 ? '-' : 'x');
	else if (val == S_ISUID || val == (S_IXUSR | S_ISUID))
		ret[2] = (val == S_ISUID ? 'S' : 's');
	ret[3] = (mode & S_IRGRP ? 'r' : '-');
	ret[4] = (mode & S_IWGRP ? 'w' : '-');
	val = mode & (S_IXGRP | S_ISGID);
	if (val == 0 || val == S_IXGRP)
		ret[5] = (val == 0 ? '-' : 'x');
	else if (val == S_ISGID || val == (S_IXGRP | S_ISGID))
		ret[5] = (val == S_ISGID ? 'S' : 's');
	ret[6] = (mode & S_IROTH ? 'r' : '-');
	ret[7] = (mode & S_IWOTH ? 'w' : '-');
	val = mode & (S_IXOTH | S_ISVTX);
	if (val == 0 || val == S_IXOTH)
		ret[8] = (val == 0 ? '-' : 'x');
	else if (val == S_ISVTX || val == (S_IXOTH | S_ISVTX))
		ret[8] = (val == S_ISVTX ? 'T' : 't');
	ret[9] = '\0';
	printf("%s", ret);
}
/*
void	print_xattr(char *path)
{
	acl_t		acl;
	acl_entry_t	dummy;
	ssize_t		xattr;
	char		sym;

	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	xattr = xattr < 0 ? 0 : xattr;
	sym = ' ';
	if (xattr > 0)
		sym = '@';
	else if (acl != NULL)
		sym = '+';
	printf("%c ", sym);
}
*/
void	print_owngroup(t_fil *file, t_cont *cont)
{
	printf("%-*s ", cont->own_len, file->owner);
	printf(" %-*s ", cont->grp_len, file->group);
}

void	print_time(struct stat stat)
{
	char *ret;

	ret = ctime(&stat.st_mtime);
	ret = ret + 4;
	*(ret + ft_strlen(ret) - 8) = '\0';
	printf(" %-.*s", (int)ft_strlen(ret) - 1, ret);
}

void	print_link(t_fil *file)
{
	
}

void	detail_print(t_cont *cont)
{
	int		i;
	t_fil	*file;

	i = 0;
	while (cont->faddr[i])
	{
		file = cont->faddr[i];
		if (file->is_dir && cont->from_av)
			return ;
		print_type(file->stat.st_mode);
		print_permissions(file->stat.st_mode);
//		print_xattr(file->full_path);
		printf(" %*lu ", cont->link_len, file->stat.st_nlink);
		print_owngroup(file, cont);
		printf(" %*ld", cont->size_len, file->stat.st_size);
		print_time(file->stat);
		printf(" %s", file->name);
		print_link(file);
		printf("\n");
		i++;
	}
}

void	onestr_print(t_cont *cont)
{
	int i;

	i = 0;
	while (cont->faddr[i])
	{
		printf("%s\n", cont->faddr[i]->name);
		i++;
	}
}

void	print_master(t_cont *cont, t_fl fl, int ac)
{
	void	(*print)(t_cont *cont);

	if (fl.l)
		print = detail_print;
	else if (fl.one)
		print = onestr_print;
	else
		print = normal_print;
	
	if (!cont->is_root && fl.up_r)
		printf("%s:\n", cont->name);
	else if (!cont->is_root && !cont->from_av && ac > 1)
	{
		printf("%s:\n", cont->name);
	}

	if (fl.l && !cont->from_av)
	{
		printf("total %ld\n", cont->total);
	}

	print(cont);
}
