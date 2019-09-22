#include "ft_ls.h"

void	set_details(t_fil *file, t_fl fl)
{
	struct stat		fst;
	struct group	*grp;
	struct passwd	*tf;

	file->group = NULL;
	file->owner = NULL;
	if ((grp = getgrgid(file->stat.st_gid)))
		file->group = ft_strdup(grp->gr_name);
	else
		perror(file->full_path);
	if ((tf = getpwuid(file->stat.st_uid)))
		file->owner = ft_strdup(tf->pw_name);
	else
		perror(file->full_path);
}

char	*set_fullname(char *fold, char *file)
{
	char	*ret;
	int		foldlen;
	int		filelen;

	foldlen = ft_strlen(fold);
	filelen = ft_strlen(file);
	if (fold[foldlen - 1] != '/')
	{
		check_malloc(ret = ft_strnew(foldlen + filelen + 1));
		ret = ft_strcat(ret, fold);
		ret = ft_strcat(ret, "/");
		ret = ft_strcat(ret, file);
	}
	else
	{
		check_malloc(ret = ft_strnew(foldlen + filelen));
		ret = ft_strcat(ret, fold);
		ret = ft_strcat(ret, file);
	}
	return (ret);
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

int	fill_files_from_path(t_cont *cont, t_fl fl)
{
	DIR				*d;
	t_fil			*head;
    struct dirent	*dir;
	int				i;
	int				flag;

	cont->mlen = 0;
	cont->fil_num = 0;
	cont->dir_num = 0;
	if (!(d = opendir(cont->name)))
	{
		perror(cont->name);
		cont->files = NULL;
		return (-1);
	}
	check_malloc(cont->files = (t_fil*)malloc(sizeof(t_fil)));
	i = 0;
	flag = 0;
	head = cont->files;
	while ((dir = readdir(d)))
		if (dir->d_name[0] != '.' || fl.a)
		{
			if (!head)
				error_exit("Unexpected error with malloc! Exiting...\n");
			if (i && !flag)
			{
				check_malloc(head->next = (t_fil*)malloc(sizeof(t_fil)));
				head = head->next;
			}
			flag = 0;
			head->full_path = set_fullname(cont->name, dir->d_name);
			if (lstat(head->full_path, &head->stat))
			{
				free(head->full_path);
				flag = 1;
				continue ;
			}
			set_details(head, fl);
			if (!head->group || !head->owner)
			{
				free(head->full_path);
				flag = 1;
				continue ;
			}
			check_malloc(head->name = ft_strdup(dir->d_name));
			cont->mlen = max(ft_strlen(dir->d_name), cont->mlen);
			cont->fil_num += (is_file(head->full_path) ? 1 : 0);
			head->is_dir = (is_file(head->full_path) ? 0 : 1);
			if (head->is_dir)
				cont->dir_num++;
			head->next = NULL;
			i++;
		}
//	check_head(&(cont->files)); CHECK FOR LAST ELEM
	cont->mlen = in_which_inter(cont->mlen);
	cont->num = i;
	closedir(d);
	if (!i)
	{
		free(cont->files);
		cont->files = NULL;
	}
	return (0);
}
