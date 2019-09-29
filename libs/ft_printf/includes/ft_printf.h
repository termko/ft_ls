/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbreiten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 03:32:43 by dbreiten          #+#    #+#             */
/*   Updated: 2019/09/18 05:26:57 by dbreiten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <string.h>
# include <stdarg.h>
# include <inttypes.h>
# include <unistd.h>

# define MAX(a,b) ((a) > (b) ? a : b)
# define MIN(a,b) ((a) < (b) ? a : b)
# define OCTAL 0
# define HEXL 1
# define HEXU 2
# define DEC 3

enum
{
	NEG = (1 << 0),
	POS = (1 << 1),
	SPACE = (1 << 2),
	OCT = (1 << 3),
	ZERO = (1 << 4)
};

enum
{
	LLPRE,
	LPRE,
	HHPRE,
	HPRE,
	JPRE,
	ZPRE,
	BASE,
};

typedef struct	s_buf
{
	int			fd;
	void		*data;
	size_t		all_size;
	size_t		curr_size;
}				t_buf;

typedef struct	s_handle
{
	int			flags;
	int			width;
	int			per;
	int			size;
	int			base;
}				t_handle;

size_t			ft_strlen(const char *s);
void			*ft_memcpy(void *dst, const void *src, size_t len);
void			*ft_memset(void *ptr, int value, size_t num);
char			*ft_strchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t len);
int				ft_atoi(const char *nptr);
int				ft_isdigit(int c);
t_buf			*create_buf(int fd, size_t size);
void			delete_buf(t_buf *buf);
void			*ft_realloc(void *src, size_t curr_size, size_t new_size);
ssize_t			write_buf(t_buf *buf, void *data, size_t size, size_t num);
ssize_t			clean_buf(t_buf *buf);
int				parse_flags(char **format);
int				parse_width(char **format, va_list list);
int				parse_per(char **format, va_list list);
int				parse_size(char **format);
ssize_t			parse_hndl_type(t_buf *buf, t_handle *hndl, char **format,
								va_list list);
ssize_t			parse_hndl_nb(t_buf *buf, t_handle *hndl, intmax_t nb);
ssize_t			parse_hndl_unb(t_buf *buf, t_handle *hndl, uintmax_t nb);
ssize_t			parse_hndl_str(t_buf *buf, t_handle *hndl, const char *str);
ssize_t			parse_hndl_sym(t_buf *buf, t_handle *hndl, char c);
char			*ft_fitoa(intmax_t nb, int perm, int show_sign);
char			*ft_fuitoa(uintmax_t n, int base, int per, int octot);

#endif
