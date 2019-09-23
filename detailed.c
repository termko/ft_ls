/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detailed.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 06:15:50 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/23 06:19:45 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			i = ft_printf(" %3d, 0x%08x", major(file->stat.st_rdev),
					(u_int)minor(file->stat.st_rdev));
		else
			i = ft_printf(" %3d, %3d", major(file->stat.st_rdev),
					minor(file->stat.st_rdev));
		cont->size_len = max(cont->size_len, i - 1);
	}
	else
		ft_printf(" %*lld", cont->size_len, file->stat.st_size);
}

void	print_owngroup(t_fil *file, t_cont *cont)
{
	ft_printf("%-*s ", cont->own_len, file->owner);
	ft_printf(" %-*s ", cont->grp_len, file->group);
}

void	print_type(mode_t mode)
{
	int val;

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
