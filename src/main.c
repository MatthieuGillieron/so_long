#include "../mlx/mlx.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../includes/get_next_line.h"


char **read_map(const char *file_path)
{
    int fd = open(file_path, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return NULL;
    }

    char **map = NULL;
    char *line;
    size_t lines_count = 0;

    while ((line = get_next_line(fd)))
    {
        // Allouer un tableau ajusté pile pour le nombre de lignes
        char **new_map = malloc((lines_count + 1 + 1) * sizeof(char *)); // +1 pour la nouvelle ligne, +1 pour le NULL
        if (!new_map)
        {
            perror("Memory allocation error");
            // Libérer la mémoire déjà allouée
            for (size_t i = 0; i < lines_count; i++)
                free(map[i]);
            free(map);
            close(fd);
            return NULL;
        }

        // Copier les anciennes lignes dans le nouveau tableau
        for (size_t i = 0; i < lines_count; i++)
            new_map[i] = map[i];

        // Ajouter la nouvelle ligne
        new_map[lines_count++] = line;
        new_map[lines_count] = NULL; // Terminer le tableau avec NULL

        // Libérer l'ancien tableau (pas les lignes, elles sont déjà dans le nouveau)
        free(map);

        // Pointer vers le nouveau tableau
        map = new_map;
    }

    close(fd);
    return map;
}









int main()
{
    void *mlx_ptr;
	void *win_ptr;

// Initialisation de la connexion avec MiniLibX
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 400, 300, "titre");
	if (!win_ptr)
		return (1);

// Lancement de la boucle d'événements
    mlx_loop(mlx_ptr);
    return (0);
}
