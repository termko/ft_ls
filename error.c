#include "ft_ls.h"

void	illegal_opt(char c)
{
	printf("ls: illegal option -- %c\nusage: ls [-Raflrt] [file ...]\n", c);
	exit(1);
}



void	print_flags(t_fl *fl)
{
	printf("FLAGS:\n");
	fl->l ? printf("l = 1\n") : fl->l;
	fl->up_r ? printf("R = 1\n") : fl->up_r;
	fl->a ? printf("a = 1\n") : fl->a;
	fl->r ? printf("r = 1\n") : fl->r;
	fl->t ? printf("t = 1\n") : fl->t;
	// fl->u ? printf("u = 1\n") : fl->u;
	fl->f ? printf("f = 1\n") : fl->f;
	// fl->p ? printf("p = 1\n") : fl->p;
}

void	print_args(char **av, int ac)
{
	int i;

	i = 0;
	printf("ARGS: %d\n", ac);
	while (av && av[i])
	{
		printf("%s  ", av[i]);
		i++;
	}
	printf("\n");
}


void	print_list(t_fil *file, int num)
{
	while (file)
	{
		printf("%16s", file->name);
		file = file->next;
	}
}

void	print_info(t_fil *file)
{
	int i = 0;
	while (file)
	{
		i++;
		printf("%s:\n", file->name);
		printf("mod time: %ld\n", file->stat.st_mtime);
		printf("mode: %d\n", file->stat.st_mode);
		printf("link: %hu\n", file->stat.st_nlink);
		printf("uid: %d\n", file->stat.st_uid);
		printf("gid: %d\n", file->stat.st_gid);
		printf("size: %lld\n", file->stat.st_size);
		printf("blocks: %lld\n", file->stat.st_blocks);
		printf("rdev: %d\n", file->stat.st_rdev);
		// exit(0);
		printf("\n\n");
		file = file->next;
	}
	printf("total: %d\n", i);
}
