/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:31:43 by mg                #+#    #+#             */
/*   Updated: 2024/12/11 11:31:46 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	is_player(t_game *game, int height, int width)
{
	mlx_put_image_to_window(game->mlx_ptr,
		game->win_ptr, game->player, width * 40, height * 40);
	game->y_axis = height;
	game->x_axis = width;
}

void	is_collect(t_game *game, int height, int width)
{
	mlx_put_image_to_window(game->mlx_ptr,
		game->win_ptr, game->collect, width * 40, height * 40);
	game->collectibles++;
}

void	set_texture(t_game *game)
{
	int	i;
	int	j;

	game->floor = mlx_xpm_file_to_image(game->mlx_ptr,
			"assets/background.xpm", &i, &j);
	game->wall = mlx_xpm_file_to_image(game->mlx_ptr,
			"assets/wall.xpm", &i, &j);
	game->player = mlx_xpm_file_to_image(game->mlx_ptr,
			"assets/player.xpm", &i, &j);
	game->exit = mlx_xpm_file_to_image(game->mlx_ptr,
			"assets/exit.xpm", &i, &j);
	game->collect = mlx_xpm_file_to_image(game->mlx_ptr,
			"assets/collect.xpm", &i, &j);
}

void	put_texture(t_game *game)
{
	int	height;
	int	width;

	game->collectibles = 0;
	height = 0;
	while (height < game->heightmap)
	{
		width = 0;
		while (game->map[height][width])
		{
			if (game->map[height][width] == '1')
				mlx_put_image_to_window(game->mlx_ptr,
					game->win_ptr, game->wall, width * 40, height * 40);
			if (game->map[height][width] == 'C')
				is_collect(game, height, width);
			if (game->map[height][width] == 'P')
				is_player(game, height, width);
			if (game->map[height][width] == 'E')
				mlx_put_image_to_window(game->mlx_ptr,
					game->win_ptr, game->exit, width * 40, height * 40);
			if (game->map[height][width] == '0')
				mlx_put_image_to_window(game->mlx_ptr,
					game->win_ptr, game->floor, width * 40, height * 40);
			width++;
		}
		height++;
	}
}
