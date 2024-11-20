#include "../mlx/mlx.h"

int main()
{
    void *mlx_ptr;
	void *win_ptr;

	mlx_ptr = mlx_init();  // Initialisation de la connexion avec MiniLibX
	win_ptr = mlx_new_window(mlx_ptr, 400, 300, "titre");
	if (!win_ptr)
		return (1);

    mlx_loop(mlx_ptr); // Lancement de la boucle d'événements

    return (0);
}
