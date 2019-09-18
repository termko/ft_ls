#include "ft_ls.h"

int		is_file(char *path)
{
    struct stat		path_stat;

	lstat(path, &path_stat);
	return (!S_ISDIR(path_stat.st_mode));
}

// void	check_if_files_exist(char **av)
// {
// 	FILE	*file;
// 	DIR		*dir;
// 	int		i;

// 	i = -1;
// 	while (av && av[++i])
// 		if (is_file(av[i]))
// 		{
// 			if ((file = fopen(av[i], "r")))
// 				fclose(file);
// 			else if ((dir = opendir(av[i])))
// 				closedir(dir);
// 			else
// 			{
// 				printf("ls: %s: No such file or directory\n", av[i]);
// 				exit(1);
// 			}
// 		}
// 		else
// 		{
// 			printf("ls: %s: No such file or directory\n", av[i]);
// 			exit(1);
// 		}
// }

int		fill_opt(t_fl *fl, char *arg)
{
	char	*flags;
	int		i;

	flags = "lRartf1";
	if (!fl || !arg)
		return (0);
	i = 0;
	while (arg[i])
	{
		if (!ft_strchr(flags, arg[i]) || (arg[0] == '-'
							&& arg[1] && arg[1] == '-'))
			illegal_opt(arg[i]);
		fl->l = arg[i] == 'l' ? 1 : fl->l;
		fl->up_r = arg[i] == 'R' ? 1 : fl->up_r;
		fl->a = arg[i] == 'a' ? 1 : fl->a;
		fl->r = arg[i] == 'r' ? 1 : fl->r;
		fl->t = arg[i] == 't' ? 1 : fl->t;
		fl->one = arg[i] == '1' ? 1 : fl->one;
		// fl->u = arg[i] == 'u' ? 1 : fl->u;
		fl->f = flags[i] == 'f' ? 1 : fl->f;
		// fl->p L= flags[i] == 'p' ? 1 : fl->p;
		i++;
	}
	return (1);
}

void		init_fl(int *ac, char ***av, t_fl *fl)
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
		i++;
	}
	*ac -= count + 1;
	*av += i;
}

t_cont	*create_cont(char *path, t_fl fl, int is_root)
{
	t_cont	*cont;
	t_fil	*tmp;

	if (!(cont = (t_cont*)malloc(sizeof(t_cont))))
		return (NULL);
	cont->name = ft_strdup(path);
	cont->dirs = NULL;
	cont->files = NULL;
	cont->is_root = is_root;
	cont->from_av = 0;
	cont->dir_num = 0;
	cont->fil_num = 0;
	cont->num = 0;
//	get_num_of_files(cont, fl);
	fill_files_from_path(cont, fl);
	fill_fileaddr(cont);
	return (cont);
}

void	create_dir(t_cont *cont, char *path, t_fl fl, int is_root)
{
	t_dirs *dir;

	if (!cont->dirs)
	{
		check_malloc(cont->dirs = (t_dirs*)malloc(sizeof(t_dirs)));
		dir = cont->dirs;
	}
	else
	{
		dir = cont->dirs;
		while (dir->next)
			dir = dir->next;
		check_malloc(dir->next = (t_dirs*)malloc(sizeof(t_dirs)));
		dir = dir->next;
	}
	dir->name = ft_strdup(path);
	dir->cont = create_cont(path, fl, is_root);
	dir->next = NULL;
}

void	set_max_len(t_cont *cont)
{
	t_fil	*head;
	long	tmp_len;
	char	*tmp;

	head = cont->files;
	cont->total = 0;
	cont->link_len = 0;
	cont->own_len = 0;
	cont->grp_len = 0;
	cont->size_len = 0;
	while (head)
	{
		cont->total += head->stat.st_blocks;
		tmp = ft_intmaxtoa(head->stat.st_nlink, 10);
		tmp_len = ft_strlen(tmp);
		free(tmp);
		cont->link_len = tmp_len > cont->link_len ? tmp_len : cont->link_len;
		if (head->owner)
		{
			tmp_len = ft_strlen(head->owner);
			cont->own_len = tmp_len > cont->own_len ? tmp_len : cont->own_len;
		}
		if (head->group)
		{
			tmp_len = ft_strlen(head->group);
			cont->grp_len = tmp_len > cont->grp_len ? tmp_len : cont->grp_len;
		}
		tmp = ft_intmaxtoa(head->stat.st_size, 10);
		tmp_len = ft_strlen(tmp);
		free(tmp);
		cont->size_len = tmp_len > cont->size_len ? tmp_len : cont->size_len;
		head = head->next;
	}
}
