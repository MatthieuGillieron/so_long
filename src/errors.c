/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:31:31 by mg                #+#    #+#             */
/*   Updated: 2024/12/16 13:05:45 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
	verif all car. sont valides
*/
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
			if (game->map[i][j] != '0' && game->map[i][j] != '1' &&
				game->map[i][j] != 'C' && game->map[i][j] != 'E' &&
				game->map[i][j] != 'P' && game->map[i][j] != '\n')
			{
				ft_printf("ERROR : invalid char : %c\n", game->map[i][j]);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

/*
	verif si entourer de murs
*/
int	check_border(t_game *game)
{
	int	x;
	int	y;

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

/*
	compte element obligatoire minimum
*/
int	check_case(t_game *game)
{
	game->nbr_player = 0;
	game->nbr_exit = 0;
	game->nbr_collect = 0;
	game->i = 0;
	while (game->map[game->i])
	{
		game->j = 0;
		while (game->map[game->i][game->j])
		{
			if (game->map[game->i][game->j] == 'P')
				game->nbr_player++;
			if (game->map[game->i][game->j] == 'E')
				game->nbr_exit++;
			if (game->map[game->i][game->j] == 'C')
				game->nbr_collect++;
			game->j++;
		}
		game->i++;
	}
	if (game->nbr_player != 1 || game->nbr_exit != 1 || game->nbr_collect == 0)
	{
		ft_printf("ERROR : 1 player, 1 exit and need min. 1 collectible.\n");
		return (0);
	}
	return (1);
}

int	empty_map(t_game *game)
{
	int	width;
	int	i;

	if (!game->map || game->map[0][0] == '\0')
	{
		ft_printf("ERROR : Empty map.\n");
		return (1);
	}
	width = same_width(game->map[0]);
	i = 1;
	while (i < game->heightmap)
	{
		if (same_width(game->map[i]) != width)
		{
			ft_printf("ERROR: Map is not rectangular.\n");
			close_game(game);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (0);
}


/*
	full verif.
*/
void	check_errors(t_game *game)
{
	if (empty_map(game))
		close_game(game);
	if (!check_map(game))
		close_game(game);
	if (!check_border(game))
	{
		ft_printf("Erreur : la carte doit être entourée de murs ('1').\n");
		close_game(game);
	}
	if (!check_case(game))
		close_game(game);
}
