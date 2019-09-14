#include "ft_ls.h"

void	free_dir(t_dirs **dir)
{
	free((*dir)->name);
	free_cont((*dir)->cont);
}

void	free_file(t_fil **file)
{
	free((*file)->full_path);
	free((*file)->name);
	if (!(*file)->is_dir)
	{
		free((*file)->group);
		free((*file)->owner);
	}
}

void	free_cont(t_cont **cont)
{
	t_dirs	*tmpdir;
	t_fil	*tmpfile;

	while ((*cont)->dirs)
	{
		tmpdir = (*cont)->dirs->next;
		free_dir((&(*cont)->dirs));
		(*cont)->dirs = tmpdir;
	}
	while ((*cont)->files)
	{
		tmpfile = (*cont)->files->next;
		free_file((&(*cont)->files));
		(*cont)->files = tmpfile;
	}
	free((*cont)->faddr);
	free((*cont)->name);
}
