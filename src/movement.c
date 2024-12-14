/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magillie <magillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:32:00 by mg                #+#    #+#             */
/*   Updated: 2024/12/14 13:38:47 by magillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

#define MOVE_MAX 2147483637

/*
	Déplace joueur si pas d'obstacle.
	Met à jour la positionet gère les interactions
*/
static int	move_player(t_game *game, int new_x, int new_y)
{
	char	position;

	position = game->map[new_y][new_x];
	if (position == '1')
		return (0);
	if (position == 'E')
	{
		if (game->collectibles == 0)
		{
			ft_printf("GG, You win !!!\n");
			close_game(game);
		}
		return (0);
	}
	if (position == 'C')
		game->collectibles--;
	game->map[game->y_axis][game->x_axis] = '0';
	game->map[new_y][new_x] = 'P';
	game->x_axis = new_x;
	game->y_axis = new_y;
	game->counter++;
	return (1);
}

/*
 	gere input clavier.
	Vérifie aussi limites map.
*/
static int	keyboard(t_game *game, int input)
{
	int	new_x;
	int	new_y;

	new_x = game->x_axis;
	new_y = game->y_axis;
	if (input == 13 || input == 126)
		new_y--;
	else if (input == 1 || input == 125)
		new_y++;
	else if (input == 0 || input == 123)
		new_x--;
	else if (input == 2 || input == 124)
		new_x++;
	else if (input == 53)
		close_game(game);
	if (new_x < 0 || new_y < 0 || new_x >= game->widthmap
		|| new_y >= game->heightmap)
		return (0);
	return (move_player(game, new_x, new_y));
}

/*
	check si trop de deplacement (int max)
*/
static void	to_much_moves(t_game *game)
{
	if (game->counter >= MOVE_MAX)
	{
		ft_printf("You'r player need sleep!! STOP WALK\n");
		close_game(game);
	}
}

/*
	effectue ttes les verifs.
*/
int	check_control(int input, t_game *game)
{
	int	ok;

		ok = keyboard(game, input);
	if (ok)
	{
		put_texture(game);
		ft_printf("Mouvement : %d\n", game->counter);
		ft_printf("Collectibles restants : %d\n", game->collectibles);
		to_much_moves(game);
	}
	return (1);
}
