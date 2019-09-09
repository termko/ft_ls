CC=clang
OUTF=ft_ls

all: 
	$(CC) *.c -o $(OUTF) libft/libft.a
