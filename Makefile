CC=gcc

all: 
	$(CC) *.c libft/libft.a libftprintf.a -Wall -Werror -Wextra

debug:
	$(CC) *.c libft/libft.a libftprintf.a -g -Wall -Werror -Wextra
