/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:58:50 by mg                #+#    #+#             */
/*   Updated: 2024/12/02 09:46:31 by mg               ###   ########.fr       */
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

	if(!textures->wall || !textures->floor || !textures->players || !textures->collect)
	{
		printf("ERROR : NO LOAD TEXTURE");
		free(textures);
		return (NULL);
	}
	return (textures);
}


void	draw_map(char **map, void *mlx_ptr, void *win_ptr, t_textures *textures)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (map[y])
	{
			x = 0;
		while(map[y][x])
		{
			if (map[y][x] == '1')
				mlx_put_image_to_window(mlx_ptr, win_ptr, textures->wall, x * TILE_SIZE, y * TILE_SIZE);
			else if (map[y][x] == '0')
				mlx_put_image_to_window(mlx_ptr, win_ptr, textures->floor, x * TILE_SIZE, y * TILE_SIZE);
			else if (map[y][x] == 'P')
				mlx_put_image_to_window(mlx_ptr, win_ptr, textures->players, x * TILE_SIZE, y * TILE_SIZE);
			else if (map[y][x] == 'C')
				mlx_put_image_to_window(mlx_ptr, win_ptr, textures->collect, x * TILE_SIZE, y * TILE_SIZE);
				
			x++;
		}
		y++;
	}
}
