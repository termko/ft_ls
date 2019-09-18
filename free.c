#include "ft_ls.h"

void	free_dir(t_dirs **dir)
{
	if ((*dir)->name)
		free((*dir)->name);
	free(*dir);
}

void	free_file(t_fil **file)
{
	if ((*file)->full_path)
		free((*file)->full_path);
	if ((*file)->name)
		free((*file)->name);
	if ((*file)->group)
		free((*file)->group);
	if ((*file)->owner)
		free((*file)->owner);
	free(*file);
}
/*
void	free_ret(char ***ret)
{
	int i;

	i = 0;
	while ((*ret)[i])
	{
	//	printf("%s\n", (*ret)[i]);
		free((*ret)[i]);
		i++;
	}
	free(*ret);
//	free((*cont)->ret);
}
*/
void	free_cont(t_cont **cont)
{
	t_fil	*tmpfile;
	t_dirs	*tmpdir;

	while ((*cont)->files)
	{
		tmpfile = (*cont)->files->next;
		free_file(&((*cont)->files));
		(*cont)->files = tmpfile;
	}
	while ((*cont)->dirs)
	{
		tmpdir = (*cont)->dirs->next;
		free_dir(&((*cont)->dirs));
		(*cont)->dirs = tmpdir;
	}
	if ((*cont)->name)
		free((*cont)->name);
//	if ((*cont)->ret)
//		free_ret(&((*cont)->ret));
	if ((*cont)->faddr)
		free((*cont)->faddr);
	free(*cont);
}
