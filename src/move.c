/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:29:43 by mg                #+#    #+#             */
/*   Updated: 2024/12/03 08:55:56 by mg               ###   ########.fr       */
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

void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x + dx;
	new_y =game->player_y +dy;

	if (game->map[new_y][new_x] != '1')
	{
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		 game->textures->floor, game->player_x * TILE_SIZE, 
		 game->player_y * TILE_SIZE);

		game->player_x = new_x;
		game->player_y = new_y;

		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		 game->textures->floor, game->player_x * TILE_SIZE, 
		 game->player_y * TILE_SIZE);
	}
}

int	keyboard(int input, t_game *game)
{
	if (input == 13 || input == 0 || input == 1 || input == 2)
	{
		game->input_count++;
		ft_printf("Input :  %d\n", game->input_count);
	}
	if (input == 13)
		move_player(game, 0, -1);
	else if (input == 0)
		move_player(game, -1, 0);
	else if (input == 1)
		move_player(game, 0, 1);
	else if (input == 2)
		move_player(game, 1, 0);
	else if (input == 53)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		free_map(game->map);
		free(game->textures);
		exit (0); // verif si exit ok pour 42
	}
	return (0);
}
