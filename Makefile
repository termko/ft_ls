CC=gcc

all: 
	$(CC) *.c libft/libft.a ft_printf/libftprintf.a -Wall -Werror -Wextra

debug:
	$(CC) *.c libft/libft.a ft_printf/libftprintf.a -g -Wall -Werror -Wextra
