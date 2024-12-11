#include "../includes/so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (0);
	ft_memset(&game, 0, sizeof(t_game));
	read_the_map(&game, argv);
	check_errors(&game);
	verify_feasibility(&game);
	game.mlx_ptr = mlx_init();
	game.win_ptr = mlx_new_window(game.mlx_ptr, (game.widthmap * 40),
			(game.heightmap * 40), "solong");
	set_texture(&game);
	put_texture(&game);
	mlx_key_hook(game.win_ptr, check_control, &game);
	mlx_hook(game.win_ptr, 17, 0, (void *)exit, 0);
	mlx_loop(game.mlx_ptr);
}
