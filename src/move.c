/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:29:43 by mg                #+#    #+#             */
/*   Updated: 2024/12/03 14:47:38 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	player_position(t_game *game)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if(game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				return;
			}
			x++;
		}
		y++;
	}
}

int move_player(t_game *game, int dx, int dy)
{
    int new_x = game->player_x + dx;
    int new_y = game->player_y + dy;

    // Vérification des obstacles : mur ou sortie inaccessible
    if (game->map[new_y][new_x] == '1' )
		return (0);

    // Si le joueur ramasse un collectible
    if (game->map[new_y][new_x] == 'C')
    {
        game->count_collect++;
        game->map[new_y][new_x] = '0';  // Remplacer le collectible par du sol
        // Redessiner la case du collectible comme un sol
        mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
            game->textures->floor, new_x * TILE_SIZE, new_y * TILE_SIZE);
    }

    // Redessiner l'ancienne position du joueur avec du sol
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
        game->textures->floor, game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);

    // Mettre à jour la position du joueur
    game->player_x = new_x;
    game->player_y = new_y;

    // Redessiner le joueur à la nouvelle position
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
        game->textures->players, game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);

    // Si tous les collectibles sont ramassés, redessiner la sortie
    if (game->count_collect - 1 == game->total_collect)
    {
        int exit_x, exit_y;
        for (exit_y = 0; game->map[exit_y]; exit_y++)
        {
            for (exit_x = 0; game->map[exit_y][exit_x]; exit_x++)
            {
                if (game->map[exit_y][exit_x] == 'E')
                    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
                        game->textures->exit, exit_x * TILE_SIZE, exit_y * TILE_SIZE);
            }
        }
    }

    return (1);
}


int	keyboard(int input, t_game *game)
{
	int	moved;

	moved = 0;

	if (input == 13)
		moved = move_player(game, 0, -1);
	else if (input == 0)
		moved = move_player(game, -1, 0);
	else if (input == 1)
		moved = move_player(game, 0, 1);
	else if (input == 2)
		moved = move_player(game, 1, 0);
	else if (input == 53)
		close_game(game);
	if (moved)
	{
		game->input_count++;
		ft_printf("Movement : %d\n", game->input_count);
	}
	return (0);
}
