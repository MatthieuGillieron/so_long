/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:01:59 by mg                #+#    #+#             */
/*   Updated: 2024/12/04 14:33:28 by mg               ###   ########.fr       */
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
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_border(char **map, size_t width, size_t height)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (x < width)
	{
		if (map[0][x] != '1' || map[height - 1][x] != '1')
			return (0);
		x++;
	}
	y = 0;
	while (y < height)
	{
		if (map[y][0] != '1' || map[y][width - 1] != '1')
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
