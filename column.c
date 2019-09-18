#include "ft_ls.h"

int get_size(t_cont *cont)
{
	struct winsize ws;
	float max_col;
	float num_lines;
	float real_col_num;

	if (cont->mlen == 0 || cont->num == 0)
		return (0);
	ioctl(0, TIOCGWINSZ, &ws);
	max_col = ws.ws_col / cont->mlen;
	num_lines = cont->num / max_col;
	if (num_lines - (int)num_lines)
		num_lines++;
	real_col_num = (float)cont->num / (int)num_lines;
	if (real_col_num - (int)real_col_num != 0)
		real_col_num++;
	cont->col = (int)real_col_num;
	cont->lin = (int)num_lines;
	if (cont->col < 1 || cont->lin < 1)
		return (0);
	return (1);
}

// char *return_filename_list(t_fil *file, int count)
// {
// int i;

// if (!file)
// return (NULL);
// i = 0;
// while (file && i < count)

// {

// i++;

// file = file->next;

// }

// return (file->name);

// }

void concat_filenames(char *to, char *name, int max_len, int full_len)
{
	int i;

	i = 0;
	while (to[i])
		i++;
	ft_strcat(to + i, name);
	i += ft_strlen(name);
	if (max_len != full_len)
		while (i < max_len)
			to[i++] = ' ';
	to[i] = '\0';
}

/*char ***/void get_structured(t_cont *cont)
{
	int i;
	int j;
	int num;
	// char **ret;
	char *name;

	check_malloc(cont->ret = (char**)malloc(sizeof(char*) * (cont->lin + 1)));
	i = -1;
	while (++i < cont->lin)
		check_malloc(cont->ret[i] = ft_strnew(cont->mlen * cont->col));
	cont->ret[i] = NULL;
	i = -1;
	while (++i < cont->lin)
	{
		j = -1;
		num = i;
		while (++j < cont->col)
		{
			if (num < cont->num)
				name = cont->faddr[num]->name;
			else
				name = NULL;
			// return_filename_list(cont->files, num);
			// printf("name = %s\n", name);
			// printf("mlen = %d\n", cont->mlen * (j + 1));
			if (name)
				concat_filenames(cont->ret[i], name, cont->mlen * (j + 1),
				cont->mlen * cont->col);
			num += cont->lin;
		}
	}
// printf("ret[0] = %s\n", cont->ret[0]);
// return (ret);
}

void normal_print(t_cont *cont)
{
	int i;
	int j;
	// char **ret;

	i = 0;
	if (!get_size(cont))
		return ;
	get_structured(cont);
	while (cont->ret[i])
		printf("%s\n", cont->ret[i++]);
}
