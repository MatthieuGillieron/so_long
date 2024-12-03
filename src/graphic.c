/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:58:50 by mg                #+#    #+#             */
/*   Updated: 2024/12/03 14:10:18 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

t_textures	*load_textures(void *mlx_ptr)
{
	t_textures *textures;

	textures = malloc(sizeof(t_textures));
	if (!textures)
		return (NULL);
	
	textures->wall = mlx_xpm_file_to_image(mlx_ptr, "assets/wall.xpm", &textures->width, &textures->height);
	textures->floor = mlx_xpm_file_to_image(mlx_ptr, "assets/background.xpm", &textures->width, &textures->height);
	textures->players = mlx_xpm_file_to_image(mlx_ptr, "assets/players.xpm", &textures->width, &textures->height);
	textures->collect = mlx_xpm_file_to_image(mlx_ptr, "assets/collect.xpm", &textures->width, &textures->height);
	textures->exit = mlx_xpm_file_to_image(mlx_ptr, "assets/exit.xpm", &textures->width, &textures->height);

	if(!textures->wall || !textures->floor || !textures->players || !textures->collect || !textures->exit)
	{
		ft_printf("ERROR : NO LOAD TEXTURE\n");
		free(textures);
		return (NULL);
	}
	return (textures);
}


void	draw_tile(t_game *game, char tile, int x, int y)
{
	void	*texture;

	texture = NULL;
			if (tile == '1')
				texture = game->textures->wall;
			else if (tile == '0')
				texture = game->textures->floor;
			else if (tile == 'P')
				texture = game->textures->players;
			else if (tile == 'C')
				texture = game->textures->collect;
			else if (tile == 'E')
			{
				if (game->count_collect == game->total_collect)
					texture = game->textures->exit;
				else
					texture = game->textures->collect;
			}

			if (texture)
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, 
				texture, x * TILE_SIZE, y * TILE_SIZE);
}

void	draw_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			draw_tile(game, game->map[y][x], x, y);
			x++;
		}
		y++;
	}
}

void	count_collect(char **map, t_game *game)
{
	size_t	y;
	size_t	x;

	y = 0;
	game->total_collect = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'C')
				game->total_collect++;
			x++;
		}
		y++;
	}
}
