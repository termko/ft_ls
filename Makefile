CC=gcc

all: 
	$(CC) *.c libft/libft.a

debug:
	$(CC) *.c libft/libft.a -g
