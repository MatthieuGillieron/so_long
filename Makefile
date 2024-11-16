NAME = so_long

SRC = so_long.c

OBJS = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra

CC = gcc

all : $(NAME)

$(NAME):
	$(CC) $(FLAGS) -c $(SRC)
	ar rcs $(NAME) $(OBJS)

clean: 
	rm -rf $(OBJS)

fclean: 
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re