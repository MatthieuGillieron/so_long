NAME = so_long

# Mettre à jour le chemin du fichier source
SRC = src/main.c
OBJS = $(SRC:.c=.o)   # Compile main.c en main.o dans le même dossier

FLAGS = -Wall -Werror -Wextra -I./mlx
CC = gcc

# Chemin vers la bibliothèque MiniLibX
MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -Lmlx -framework OpenGL -framework AppKit

# Règle par défaut
all: $(NAME)

# Compilation de l'exécutable
$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

# Règle pour compiler main.c en main.o
$(OBJS): src/main.c
	$(CC) $(FLAGS) -c src/main.c -o src/main.o

clean:
	rm -rf $(OBJS)

fclean:
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
