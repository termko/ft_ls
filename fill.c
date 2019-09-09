#include "ft_ls.h"

void	set_details(t_fil *file)
{
	struct stat		fst;
	struct group	*grp;
	struct passwd	*tf;

	while (file)
	{
		if (!lstat(file->full_path, &file->stat))
		{
			if (!(grp = getgrgid(file->stat.st_gid)))
				file->group = NULL;
			else
				file->group = ft_strdup(grp->gr_name);
			if (!(tf = getpwuid(file->stat.st_uid)))
				file->owner = NULL;
			else
				file->owner = ft_strdup(tf->pw_name);
		}
		if (!file->owner || !file->group)
			printf("ERROR LSTAT\n");
		file = file->next;
	}
}

void	fill_files_from_path(t_dirs *fold, t_fl fl)
{
	DIR				*d;
	t_fil			*head;
    struct dirent	*dir;
	int				i;
	int				len;

	if (!(fold->file = (t_fil*)malloc(sizeof(t_fil)))
		|| !(d = opendir(fold->name)))
		return ;
	i = 0;
	head = fold->file;
	while ((dir = readdir(d)))
		if (dir->d_name[0] != '.' || fl.a)
		{
			i++;
			head->full_path = ft_strjoin(fold->name, dir->d_name);
			head->name = ft_strdup(dir->d_name);
			head->next = i < fold->fil_num + fold->dir_num ?
				(t_fil*)malloc(sizeof(t_fil)) : NULL;
			head = head->next;
		}
	closedir(d);
	set_details(fold->file);
}

void	len_count(t_dirs *dir)
{
	t_fil		*file;
	int			len;
	struct stat	stats;

	file = dir->file;
	while (file)
	{
		len = ft_strlen(ft_intmaxtoa(stats.st_nlink, 10));
		dir->link_len = (len > dir->link_len ? len : dir->link_len);
		len = ft_strlen(file->group);
		dir->grp_len = (len > dir->grp_len ? len : dir->grp_len);
		len = ft_strlen(file->owner);
		dir->own_len = (len > dir->own_len ? len : dir->own_len);
		len = ft_strlen(ft_intmaxtoa(stats.st_size, 10));
		dir->size_len = (len > dir->size_len ? len : dir->size_len);
		file = file->next;
	}
}

int in_which_inter(int max_len)
{
	int plus_8;

	plus_8 = 0;
	while (max_len >= plus_8)
		plus_8 += 8;
	max_len = plus_8;
    return (max_len);
}

void	get_num_of_files(t_dirs *fold, int fl_a)
{
	DIR				*d;
    unsigned int	len;
	int				ret;
    struct dirent	*dir;

    fold->mlen = 0;
	fold->fil_num = 0;
	ret = 0;
    if (!(d = opendir(fold->name)))
		return ;
	while ((dir = readdir(d)))
		if (dir->d_name[0] != '.' || fl_a)
		{
			len = ft_strlen(dir->d_name);
           	fold->mlen = len > fold->mlen ? len : fold->mlen;
			fold->fil_num += is_file(dir->d_name) ? 1: 0;
			ret++;
		}
	closedir(d);
	fold->mlen = in_which_inter(fold->mlen);
	fold->dir_num = ret - fold->fil_num;
	fold->num = fold->dir_num + fold->fil_num;
}
