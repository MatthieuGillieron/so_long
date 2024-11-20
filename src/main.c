#include "mlx.h"

#include "mlx.h"

int main()
{
    void *mlx;

    mlx = mlx_init();  // Initialisation de la connexion avec MiniLibX

    mlx_pixel_put(mlx, mlx, 400, 300, 0x00FF00); // Affichage d'un pixel vert

    mlx_loop(mlx); // Lancement de la boucle d'événements

    return (0);
}

