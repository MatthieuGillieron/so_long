/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:27:23 by mg                #+#    #+#             */
/*   Updated: 2024/12/03 11:22:46 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/so_long.h"


static int	init_game(t_game *game, char *path)
{
	game->input_count = 0;
	game->map = read_map(path);
	if (!game->map)
		return (ft_printf("ERROR : Map is Broke :( !!\n"), 0);
	player_position(game);
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (ft_printf("ERROR : Init map is Broke :( !!\n"), 0);
	game->textures = load_textures(game->mlx_ptr);
	if (!game->textures)
		return (ft_printf("ERROR : Load Texture is Broke :( !!\n"), 0);
	return (1);
}


void	cleanup(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	free_map(game->map);
	free(game->textures);
}

int main(void)
{
    t_game game;
    size_t	map_width;
	size_t	map_height;
    int	window_width;
	int	window_height;

    if (!init_game(&game, "map/classic.ber"))
		return (1);
	map_dimension(game.map, &map_width, &map_height);
	window_width = map_width * TILE_SIZE;
	window_height = map_height * TILE_SIZE;
	game.win_ptr = mlx_new_window(game.mlx_ptr, window_width,
	 window_height, "so_long");
	if (!game.win_ptr)
		return (ft_printf("ERROR : Create window Broke !\n"), 1);
	draw_map(&game);
	mlx_hook(game.win_ptr, 17, 0, close_game, &game);
	mlx_key_hook(game.win_ptr, keyboard, &game);
	mlx_loop(game.mlx_ptr);
	cleanup(&game);
    return (0);
}
