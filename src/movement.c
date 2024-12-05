/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:29:43 by mg                #+#    #+#             */
/*   Updated: 2024/12/04 13:50:41 by mg               ###   ########.fr       */
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


int	update_position(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == '1')
		return (0);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
	game->textures->floor,
	game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);
	game->player_x = new_x;
	game->player_y = new_y;
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
	game->textures->players, game->player_x * TILE_SIZE,
	game->player_y * TILE_SIZE);
	return (1);
}

void	collect_item(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'C')
	{
		game->count_collect++;
		game->map[new_y][new_x] = '0';
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->textures->floor, new_x * TILE_SIZE, new_y * TILE_SIZE);
	}
}

void	game_end(t_game *game, int new_x, int new_y)
{
		if (game->count_collect - 1 == game->total_collect)
		{
			int	exit_x;
			int	exit_y;

			exit_y = 0;
			while (game->map[exit_y])
			{
				exit_x = 0;
				while (game->map[exit_y][exit_x])
				{
					if (game->map[exit_y][exit_x] == 'E')
						mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
						game->textures->exit,
						exit_x * TILE_SIZE, exit_y * TILE_SIZE);					
					exit_x++;
				}
				exit_y++;
			}
			if (game->map[new_y][new_x] == 'E')
			{
				ft_printf("You win!\n");
				close_game(game);
				exit(0);
			}
		}
}

int	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	collect_item(game, new_x, new_y);
	if (update_position(game, new_x, new_y))
	{
		game_end(game, new_x, new_y);
		return (1);
	}
	return (0);
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
