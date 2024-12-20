/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:31:43 by mg                #+#    #+#             */
/*   Updated: 2024/12/16 12:56:24 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
	met image joueur et met a jour coordonnée dans struct
*/
void	is_player(t_game *game, int height, int width)
{
	mlx_put_image_to_window(game->mlx_ptr,
		game->win_ptr, game->player, width * PIX, height * PIX);
	game->y_axis = height;
	game->x_axis = width;
}

/*
	met image + incremente collect
*/
void	is_collect(t_game *game, int height, int width)
{
	mlx_put_image_to_window(game->mlx_ptr,
		game->win_ptr, game->collect, width * PIX, height * PIX);
	game->collectibles++;
}

/*
	charge texture et stock dans la struct
*/
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
	if (!game->floor || !game->wall
		|| !game->player || !game->exit || !game->collect)
	{
		ft_printf("Error: Failed to load textures.\n");
		exit(EXIT_FAILURE);
	}
}

/*
	met les textures sur la fenetre selon map etc.. 
	(h est height et w width pour gagner ligne)
*/
void	put_texture(t_game *game)
{
	game->collectibles = 0;
	game->h = 0;
	while (game->h < game->heightmap)
	{
		game->w = 0;
		while (game->map[game->h][game->w])
		{
			if (game->map[game->h][game->w] == '1')
				mlx_put_image_to_window(game->mlx_ptr,
					game->win_ptr, game->wall, game->w * PIX, game->h * PIX);
			if (game->map[game->h][game->w] == 'C')
				is_collect(game, game->h, game->w);
			if (game->map[game->h][game->w] == 'P')
				is_player(game, game->h, game->w);
			if (game->map[game->h][game->w] == 'E')
				mlx_put_image_to_window(game->mlx_ptr,
					game->win_ptr, game->exit, game->w * PIX, game->h * PIX);
			if (game->map[game->h][game->w] == '0')
				mlx_put_image_to_window(game->mlx_ptr,
					game->win_ptr, game->floor, game->w * PIX, game->h * PIX);
			game->w++;
		}
		game->h++;
	}
}
