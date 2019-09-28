/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 06:09:19 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/28 19:29:16 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	first_perm(char *ret, mode_t mode)
{
	int		val;

	ret[0] = (mode & S_IRUSR ? 'r' : '-');
	ret[1] = (mode & S_IWUSR ? 'w' : '-');
	val = mode & (S_IXUSR | S_ISUID);
	if (val == 0 || val == S_IXUSR)
		ret[2] = (val == 0 ? '-' : 'x');
	else if (val == S_ISUID || val == (S_IXUSR | S_ISUID))
		ret[2] = (val == S_ISUID ? 'S' : 's');
}

void	second_perm(char *ret, mode_t mode)
{
	int		val;

	ret[3] = (mode & S_IRGRP ? 'r' : '-');
	ret[4] = (mode & S_IWGRP ? 'w' : '-');
	val = mode & (S_IXGRP | S_ISGID);
	if (val == 0 || val == S_IXGRP)
		ret[5] = (val == 0 ? '-' : 'x');
	else if (val == S_ISGID || val == (S_IXGRP | S_ISGID))
		ret[5] = (val == S_ISGID ? 'S' : 's');
}

void	third_perm(char *ret, mode_t mode)
{
	int		val;

	ret[6] = (mode & S_IROTH ? 'r' : '-');
	ret[7] = (mode & S_IWOTH ? 'w' : '-');
	val = mode & (S_IXOTH | S_ISVTX);
	if (val == 0 || val == S_IXOTH)
		ret[8] = (val == 0 ? '-' : 'x');
	else if (val == S_ISVTX || val == (S_IXOTH | S_ISVTX))
		ret[8] = (val == S_ISVTX ? 'T' : 't');
}

void	print_permissions(mode_t mode)
{
	char	*ret;

	check_malloc(ret = (char*)malloc(sizeof(char) * 10));
	first_perm(ret, mode);
	second_perm(ret, mode);
	third_perm(ret, mode);
	ret[9] = '\0';
	ft_printf("%s", ret);
	free(ret);
}
