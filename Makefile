CC = gcc
CFLAGS = -Wall -Wextra -Werror libft/libft.a ft_printf/libftprintf.a
SRC = args_help.c column.c detailed.c error.c fill.c fill_help.c flags.c free.c\
	  from_args.c help_sort.c helpers.c init.c main.c master.c permissions.c\
	  print.c sort.c utils.c
OBJ = args_help.o column.o detailed.o error.o fill.o fill_help.o flags.o free.o\
	  from_args.o help_sort.o helpers.o init.o main.o master.o permissions.o\
	  print.o sort.o utils.o
HDR = ft_ls.h
NAME = ft_ls
LIBMAKE = libft
PRINTFMAKE = ft_printf


all:		$(NAME)

$(NAME):	$(LIBMAKE) $(SRC) $(HDR) $(PRINTFMAKE)
	@make --directory=$(LIBMAKE)
	@make --directory=$(PRINTFMAKE)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	@rm -rf $(OBJ)
	@make --directory=$(LIBMAKE) clean
	@make --directory=$(PRINTFMAKE) clean

fclean:		clean
	@rm -rf $(NAME)
	@make --directory=$(LIBMAKE) fclean
	@make --directory=$(PRINTFMAKE) fclean

re:			fclean all

debug:
	$(CC) $(CFLAGS) $(SRC) -o $(NAME) -g
