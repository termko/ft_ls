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

void	fill_files_from_path(t_cont *cont, t_fl fl)
{
	DIR				*d;
	t_fil			*head;
    struct dirent	*dir;
	int				i;
	int				len;

	if (!(cont->files = (t_fil*)malloc(sizeof(t_fil)))
		|| !(d = opendir(cont->name)))
		return ;
	i = 0;
	head = cont->files;
	while ((dir = readdir(d)))
		if (dir->d_name[0] != '.' || fl.a)
		{
			if (!head)
			{
				ft_putendl("Unexpected error with malloc! Exiting...");
				exit(1);
			}
			i++;
			head->full_path = ft_strjoin(cont->name, dir->d_name);
			head->name = ft_strdup(dir->d_name);
			head->next = i < cont->num ?
				(t_fil*)malloc(sizeof(t_fil)) : NULL;
			head = head->next;
		}
	closedir(d);
	set_details(cont->files);
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

void	get_num_of_files(t_cont *cont, int fl_a)
{
	DIR				*d;
    unsigned int	len;
	int				ret;
    struct dirent	*dir;

    cont->mlen = 0;
	cont->fil_num = 0;
	ret = 0;
    if (!(d = opendir(cont->name)))
		return ;
	while ((dir = readdir(d)))
		if (dir->d_name[0] != '.' || fl_a)
		{
			len = ft_strlen(dir->d_name);
           	cont->mlen = len > cont->mlen ? len : cont->mlen;
			cont->fil_num += is_file(dir->d_name) ? 1: 0;
			ret++;
		}
	closedir(d);
	cont->mlen = in_which_inter(cont->mlen);
	cont->dir_num = ret - cont->fil_num;
	cont->num = ret;
}
