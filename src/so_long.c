/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:27:23 by mg                #+#    #+#             */
/*   Updated: 2024/12/05 13:54:51 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/so_long.h"




void	cleanup(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	free_map(game->map);
	free(game->textures);
}


void	init_game(t_game *game)
{
	game->mlx_ptr = mlx_init(); // Initialisation de mlx
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->widthmap * TILE_SIZE, 
					game->heightmap * TILE_SIZE, "So Long"); // Création de la fenêtre
	game->textures = load_textures(game->mlx_ptr); // Charger les textures
}


int	main(int argc, char **argv)
{
	t_game	game;

	// Vérifier les erreurs liées au fichier d'entrée
	if (argc != 2)
	{
		ft_printf("ERROR: Invalid number of arguments.\n");
		return (1);
	}
	// Charger la carte
	game.map = read_map(argv[1]);
	if (!game.map)
	{
		ft_printf("ERROR: Failed to load the map.\n");
		return (1);
	}

	// Calculer les dimensions de la carte
	map_dimension(game.map, &game);

	// Vérifier la validité de la carte
	check_errors(&game);  // Appel à la fonction qui vérifie la carte

	// Initialisation de la fenêtre
	game.mlx_ptr = mlx_init();
	if (!game.mlx_ptr)
	{
		ft_printf("ERROR: Failed to initialize mlx.\n");
		return (1);
	}
	game.win_ptr = mlx_new_window(game.mlx_ptr, game.widthmap * TILE_SIZE,
			game.heightmap * TILE_SIZE, "So Long");
	if (!game.win_ptr)
	{
		ft_printf("ERROR: Failed to create window.\n");
		return (1);
	}

	// Charger les textures
	game.textures = load_textures(game.mlx_ptr);
	if (!game.textures)
	{
		ft_printf("ERROR: Failed to load textures.\n");
		return (1);
	}

	// Trouver la position du joueur
	player_position(&game);

	// Afficher la carte
	draw_map(&game);

	// Gérer les événements du clavier
	mlx_key_hook(game.win_ptr, keyboard, &game);
	mlx_hook(game.win_ptr, 17, 0, close_game, &game);

	// Lancer le jeu
	mlx_loop(game.mlx_ptr);

	return (0);
}
