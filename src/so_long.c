/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:27:23 by mg                #+#    #+#             */
/*   Updated: 2024/11/29 10:57:04 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/so_long.h"

int main(void)
{
    t_game game;
    size_t map_width, map_height;
    int window_width, window_height;

    game.input_count = 0;
    game.map = read_map("map/classic.ber");
    if (!game.map)
        return (ft_printf("[ERROR] -> MAP BROKE\n"), 1);

    player_position(&game);
    game.mlx_ptr = mlx_init();
    if (!game.mlx_ptr)
        return (ft_printf("[ERROR] -> INIT BROKE\n"), 1);

    map_dimension(game.map, &map_width, &map_height);
    window_width = map_width * TILE_SIZE;
    window_height = map_height * TILE_SIZE;

    game.win_ptr = mlx_new_window(game.mlx_ptr, window_width, window_height, "So Long");
    if (!game.win_ptr)
        return (ft_printf("ERREUR : Impossible de créer la fenêtre\n"), 1);

    game.textures = load_textures(game.mlx_ptr);
    if (!game.textures)
        return (ft_printf("[ERROR] -> LOAD BROKE\n"), 1);

    draw_map(game.map, game.mlx_ptr, game.win_ptr, game.textures);
    mlx_key_hook(game.win_ptr, keyboard, &game);
    mlx_loop(game.mlx_ptr);

    free_map(game.map);
    free(game.textures);
    return (0);
}
