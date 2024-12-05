/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:01:59 by mg                #+#    #+#             */
/*   Updated: 2024/12/05 14:42:53 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_char_map(char c)
{
	if (c != '0' && c != '1' && c != 'C' && c != 'E' && c != 'P')
		return (0);
	return (1);
}


int	check_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (!check_char_map(game->map[i][j]))
			{
	            ft_printf("Caractère invalide trouvé : %c\n", game->map[i][j]);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_border(t_game *game)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (x < game->widthmap)
	{
		if (game->map[0][x] != '1' || game->map[game->heightmap - 1][x] != '1')
			return (0);
		x++;
	}
	y = 0;
	while (y < game->heightmap)
	{
		if (game->map[y][0] != '1' || game->map[y][game->widthmap - 1] != '1')
			return (0);
		y++;
	}
	return (1);
}

int	check_is_valid(t_game *game)
{
	int	player_count;
	int	exit_count;
	int	collect_count;
	int i;
	int j;

	player_count = 0;
	exit_count = 0;
	collect_count = 0;
	i = 0;
	while(game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'P')
				player_count++;
			if (game->map[i][j] == 'E')
				exit_count++;
			if (game->map[i][j] == 'C')
				collect_count++;
			j++;
		}
		i++;
	}
	if (player_count != 1 || exit_count != 1 || collect_count == 0)
		return (0);
	return (1);
}

int	map_empty(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] != '\n')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}




void	check_errors(t_game *game)
{
	
	if (map_empty(game))
	{
		ft_printf("Erreur : la carte est vide\n");
		close_game(game);
	}
	if (!check_map(game))
	{
		ft_printf("Erreur : la carte contient des caractères invalides\n");
		close_game(game);
	}
	if (!check_border(game))
	{
		ft_printf("Erreur : les murs de la carte sont incorrects\n");
		close_game(game);
	}
	if (!check_is_valid(game))
	{
		ft_printf("Erreur : la carte doit avoir exactement un joueur, une sortie et au moins un collectible\n");
		close_game(game);
	}
	verify_feasibility(game);
}