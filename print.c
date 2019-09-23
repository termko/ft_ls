/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 02:08:07 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/23 06:07:56 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_type(mode_t mode)
{
	int	val;

	val = mode & S_IFMT;
	if (val == S_IFBLK)
		ft_printf("b");
	else if (val == S_IFCHR)
		ft_printf("c");
	else if (val == S_IFLNK)
		ft_printf("l");
	else if (val == S_IFIFO)
		ft_printf("p");
	else if (val == S_IFDIR)
		ft_printf("d");
	else if (val == S_IFSOCK)
		ft_printf("s");
	else if (val == S_IFREG)
		ft_printf("-");
	else
		ft_printf("?");
}

void	print_permissions(mode_t mode)
{
	int		val;
	char	ret[10];

/*
	ret[0] = (mode & S_IRUSR ? 'r' : '-');
	ret[1] = (mode & S_IWUSR ? 'w' : '-');
	val = mode & (S_IXUSR | S_ISUID);
	if (val == 0 || val == S_IXUSR)
		ret[2] = (val == 0 ? '-' : 'x');
	else if (val == S_ISUID || val == (S_IXUSR | S_ISUID))
		ret[2] = (val == S_ISUID ? 'S' : 's');
*/
	first_perm(ret, mode);
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
	ft_printf("%s", ret);
}

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
	ft_printf("%c ", sym);
}

void	print_owngroup(t_fil *file, t_cont *cont)
{
	ft_printf("%-*s ", cont->own_len, file->owner);
	ft_printf(" %-*s ", cont->grp_len, file->group);
}

void	print_time(struct stat stat)
{
	char	*ret;
	long	tmp;
	char	*print;
	int		i;

	ret = ctime(&stat.st_mtime);
	time(&tmp);
	ret = ret + 4;
	if (ft_labs(tmp - stat.st_mtime) > 15768000)
	{
		printf(" ");
		i = 0;
		while (i < 7)
			ft_printf("%c", ret[i++]);
		i = 16;
		printf(" ");
		while (i < 20)
			ft_printf("%c", ret[i++]);
	}
	else
	{
		*(ret + ft_strlen(ret) - 8) = '\0';
		ft_printf(" %-.*s", (int)ft_strlen(ret) - 1, ret);
	}
}

void	print_link(t_fil *file)
{
	char	*linkname;
	long	r;

	check_malloc(linkname = (char*)malloc(sizeof(char) * file->stat.st_size));
	if ((r = readlink(file->full_path, linkname, file->stat.st_size)) > 0)
		ft_printf(" -> %s", linkname);
	ft_strdel(&linkname);
}

void	print_size(t_cont *cont, t_fil *file)
{
	int i;

	if (S_ISCHR(file->stat.st_mode) || S_ISBLK(file->stat.st_mode))
	{
		if (minor(file->stat.st_rdev) > 255 || minor(file->stat.st_rdev) < 0)
			i = ft_printf(" %3d, 0x%08x", major(file->stat.st_rdev), (u_int)minor(file->stat.st_rdev));
		else
			i = ft_printf(" %3d, %3d", major(file->stat.st_rdev), minor(file->stat.st_rdev));
		cont->size_len = max(cont->size_len, i - 1);
	}
	else
		ft_printf(" %*lld", cont->size_len, file->stat.st_size);
}

void	detail_print(t_cont *cont, t_fl fl)
{
	int		i;
	t_fil	*file;

	i = 0;
	while (cont->faddr[i])
	{
		file = cont->faddr[i];
		if (file->is_dir && cont->from_av && cont->is_root)
			return ;
		print_type(file->stat.st_mode);
		print_permissions(file->stat.st_mode);
		print_xattr(file->full_path);
		ft_printf("%*hu ", cont->link_len, file->stat.st_nlink);
		print_owngroup(file, cont);
		print_size(cont, file);
		print_time(file->stat);
		ft_printf(" %s", file->name);
		print_link(file);
		ft_printf("\n");
		i++;
	}
}

void	onestr_print(t_cont *cont, t_fl fl)
{
	int i;

	i = 0;
	while (cont->faddr[i])
	{
		ft_printf("%s\n", cont->faddr[i]->name);
		i++;
	}
}

void	print_master(t_cont *cont, t_fl fl, int ac)
{
	void	(*print)(t_cont *cont, t_fl fl);

	if (fl.l)
		print = detail_print;
	else if (fl.one)
		print = onestr_print;
	else
		print = normal_print;
	if (!cont->is_root && cont->from_av && ac > 1)
	{
		ft_printf("%s:\n", cont->name);
	}
	else if (!cont->is_root && fl.up_r && (!cont->from_av || ac > 1))
	{
		ft_printf("%s:\n", cont->name);
	}
	if (fl.l && (!cont->from_av || !cont->is_root) && cont->files)
	{
		ft_printf("total %ld\n", cont->total);
	}
	print(cont, fl);
}
