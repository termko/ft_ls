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

void	print_owngroup(t_fil *file, t_dirs *dir)
{
	printf("%-*s ", dir->own_len, file->owner);
	printf(" %-*s ", dir->grp_len, file->group);
}

void	print_time(struct stat stat)
{
	char *ret;

	ret = ctime(&stat.st_mtime);
	ret = ret + 4;
	*(ret + ft_strlen(ret) - 8) = '\0';
	printf(" %-.*s", ft_strlen(ret) - 1, ret);
}

void	print_link(t_fil *file)
{
	
}

void	detail_print(t_dirs *dir, t_fil *file)
{
	if (file->is_dir)
		return ;
	print_type(file->stat.st_mode);
	print_permissions(file->stat.st_mode);
	print_xattr(file->full_path);
	printf("%*d ", dir->link_len, file->stat.st_nlink);
	print_owngroup(file, dir);
	printf(" %*lld", dir->size_len, file->stat.st_size);
	print_time(file->stat);
	printf(" %s", file->name);
	print_link(file);
	printf("\n");
}

void	normal_print(t_dirs *dir, t_fil *file)
{
	printf("%s\n", file->name);
}

void	onestr_print(t_dirs *dir, t_fil *file)
{
	printf("%s\n", file->name);
}

void	print_master(t_dirs *dir, t_fl fl)
{
	void	(*print)(t_dirs *dir, t_fil *file);
	int		i;
	int		flag;

	if (fl.l)
		print = detail_print;
	else if (fl.one)
		print = onestr_print;
	else
		print = normal_print;
	flag = 0;
	while (dir)
	{
		if (!dir->is_root && fl.l && !dir->from_av)
			printf("total %ld\n", dir->total);
		i = 0;
		while (dir->faddr[i])
		{
			print(dir, dir->faddr[i]);
			i++;
		}
		dir = dir->next;
	}
}
