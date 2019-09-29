CC = gcc
FLAGS = -Wall -Wextra -Werror
LIBNAME = libftprintf.a
SRC = srcs/ft_atoi.c srcs/ft_buf.c srcs/ft_fitoa.c srcs/ft_fuitoa.c\
	  srcs/ft_isdigit.c srcs/ft_memcpy.c srcs/ft_memset.c srcs/ft_strchr.c\
	  srcs/ft_strlen.c srcs/ft_strncmp.c srcs/main.c srcs/parse_dig.c\
	  srcs/parse_hndl.c srcs/parse_sym.c srcs/parse_types.c

all:
	@$(CC) $(FLAGS) -c $(SRC)
	@ar cr $(LIBNAME) *.o

clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(LIBNAME)

re: fclean all
