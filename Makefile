NAME = so_long

SRC = $(wildcard src/*.c)
GNL = $(wildcard gnl/*.c)
PRINTF = $(wildcard printf/*.c)
HEADERS = $(wildcard include/*.h)
OBJS = $(SRC:.c=.o) $(GNL:.c=.o) $(PRINTF:.c=.o)

FLAGS = -Wall -Werror -Wextra -I./mlx
CC = gcc

MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -Lmlx -framework OpenGL -framework AppKit


all: $(NAME)


$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)


$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)


%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean:
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
