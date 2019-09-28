/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 14:06:22 by ydavis            #+#    #+#             */
/*   Updated: 2019/09/28 18:50:57 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	illegal_opt(char c)
{
	char *one;
	char *two;

	one = "ls: illegal option -- ";
	two = "\nusage: ls [-1Raflprt] [file ...]\n";
	write(STDERR_FILENO, one, ft_strlen(one));
	write(STDERR_FILENO, &c, 1);
	write(STDERR_FILENO, two, ft_strlen(two));
	exit(EXIT_FAILURE);
}

void	just_perror(char *name)
{
	ft_fprintf(2, "ft_ls: ");
	perror(name);
}
