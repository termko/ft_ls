#ifndef FT_LS_H
# define FT_LS_H


# include "libft/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <time.h>
# include <stdio.h>
//---------------------
# include <sys/ioctl.h> //can be cheating, but just trying
//---------------------
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# define BUFF_SIZE 255
//----
#include <stdio.h>
//----


typedef struct	s_msize
{

}				t_msize;

typedef struct	s_fil
{
	char			*full_path;
	char			*name;
	struct stat		stat;
	char			*group;
	char			*owner;
	int				is_dir;
	struct s_fil	*next;
}				t_fil;

typedef struct	s_dirs
{
	char	*name;
	char	*slash;
	t_fil	*file;
	int		num;
	int		fil_num;
	int		dir_num;
	int		mlen;
	int		is_root;
	int		from_av;

	long	total;
	int		link_len;
	int		own_len;
	int		grp_len;
	int		size_len;

	t_fil	**faddr;

	struct s_dirs	*next;
}				t_dirs;


typedef struct		s_fl
{
	int				l;
    int				up_r;
	int				one;
    int				a; 		//complete
	int				r; 		//complete
	int				t;		//complete
    // int				u;
	int				f;		//complete
	// int				p;
}					t_fl;

typedef struct	s_prl
{
	struct stat	fst;
	long		total;
	int			link_len;
	int			owner_len;
	int			group_name;
	int			st_size_len;
	int			i;
	char		**full_path;
} 				t_prl;

//-----------------error.c
void	illegal_opt(char c);
void	print_flags(t_fl *fl);
void	print_args(char **av, int ac);

//-----------------init.c
int		fill_opt(t_fl *fl, char *arg);
void	init_fl(int *ac, char ***av, t_fl *fl);
int		is_file(char *path);
void	set_max_len(t_dirs *fold, t_fl fl);
// void	check_if_files_exist(char **av);


t_dirs	*create_dir(char *path, t_fl fl, int is_root);
t_dirs	*set_path(int ac, char **av, t_fl fl);


//------------------sort.c
void	first_sort(char **arg);
void	sort_master(t_dirs *dir, t_fl fl);
int		sort_standart(t_fil *a, t_fil *b);
int		sort_rev(t_fil *a, t_fil *b);

//------------------fill.c
void	fill_files_from_path(t_dirs *fold, t_fl fl);
void	get_num_of_files(t_dirs *fold, int fl_a);

//------------------utils.c
void	check_malloc(void *addr);
void	fill_fileaddr(t_dirs *dir);

//------------------print.c
void	print_master(t_dirs *dir, t_fl fl);
#endif
