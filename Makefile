NAME = so_long

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iheaders

MLX_DIR = ./minilibx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

SRC = $(wildcard src/*.c)
GNL = $(wildcard gnl/*.c)
PRINTF = $(wildcard printf/*.c)
OBJ = $(SRC:.c=.o) $(GNL:.c=.o) $(PRINTF:.c=.o)

all: $(MLX_LIB) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
