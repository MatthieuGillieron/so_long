NAME = libftprintf.a

SRC = fonction_print_1.c fonction_print_2.c noyau.c utilitaires.c

OBJS = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra

CC = gcc

HEADER = ft_pritnf.h

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) -c $(SRC)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)
	

fclean: clean
	rm -f $(NAME)

re: fclean all