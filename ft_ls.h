/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 20:13:15 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/29 20:16:01 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft/inc/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <time.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <sys/syslimits.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <sys/xattr.h>
# include "ft_printf/libftprintf.h"
# define BUFF_SIZE 255

int					g_ret;

struct s_cont;

typedef struct		s_fil
{
	char			*full_path;
	char			*name;
	struct stat		stat;
	char			*group;
	char			*owner;
	int				is_dir;
	struct s_fil	*next;
}					t_fil;

typedef struct		s_dirs
{
	char			*name;
	struct s_cont	*cont;
	struct s_dirs	*next;
}					t_dirs;

typedef struct		s_fl
{
	int				l;
	int				up_r;
	int				one;
	int				a;
	int				r;
	int				t;
	int				f;
	int				p;
}					t_fl;

typedef struct		s_cont
{
	t_fil	*files;
	t_dirs	*dirs;
	char	*name;
	int		is_root;
	int		from_av;
	long	total;
	int		link_len;
	int		own_len;
	int		grp_len;
	int		size_len;
	int		lin;
	int		col;
	char	**ret;
	int		num;
	int		fil_num;
	int		dir_num;
	int		mlen;
	t_fil	**faddr;
}					t_cont;

void				illegal_opt(char c);
void				print_flags(t_fl *fl);
void				print_args(char **av, int ac);
void				error_exit(char *err);
void				just_perror(char *name);
int					fill_opt(t_fl *fl, char *arg);
void				init_fl(int *ac, char ***av, t_fl *fl);
int					is_file(char *path);
void				set_max_len(t_cont *cont);
void				create_dir(t_cont *cont, char *path, t_fl fl, int is_root);
t_cont				*create_cont(char *path, t_fl fl, int is_root);
t_cont				*set_path(int ac, char **av, t_fl fl);
void				first_sort(char **arg);
void				sort_master(t_cont *cont, t_fl fl);
int					sort_standart(t_fil *a, t_fil *b);
int					sort_rev(t_fil *a, t_fil *b);
int					sort_time(t_fil *a, t_fil *b);
int					sort_timerev(t_fil *a, t_fil *b);
int					fill_files_from_path(t_cont *cont, t_fl fl);
void				get_num_of_files(t_cont *cont, t_fl fl);
int					in_which_inter(int max_len);
char				*set_fullname(char *fold, char *file);
void				set_details(t_fil *file);
void				check_malloc(void *addr);
void				fill_fileaddr(t_cont *cont);
int					max(int a, int b);
long				ft_labs(long a);
void				normal_print(t_cont *cont, t_fl fl);
void				print_master(t_cont *cont, t_fl fl, int ac);
void				print_link(t_fil *file);
void				print_size(t_cont *cont, t_fil *file);
void				print_owngroup(t_fil *file, t_cont *cont);
void				print_type(mode_t mode);
void				print_permissions(mode_t mode);
void				fill_flags(t_fl *fl, char c);
void				sort_print(t_cont *cont, t_fl fl, int ac);
t_cont				*init_cont(void);
void				check_file(t_cont *cont, struct stat st,
					t_fl fl, char *file);
void				failed_fill(t_cont *cont, t_fil *file);
void				fill_owngroup(t_fil *file);
int					fill_check(t_cont *cont, t_fil *file, char *name, t_fl fl);
void				check_head(t_fil **files, int count);
int					fill_cycle(DIR *d, t_cont *cont, t_fl fl, t_fil *head);
void				free_cont(t_cont **cont);
void				free_file(t_fil **file);
#endif
