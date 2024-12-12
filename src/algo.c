/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:31:37 by mg                #+#    #+#             */
/*   Updated: 2024/12/11 19:43:33 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
	init tab. pour marquer les cases visité
*/
static int	**init_visited(t_game *game)
{
	int	**visited;
	int	i;
	int	j;

	visited = malloc(sizeof(int *) * game->heightmap);
	if (!visited)
		free_int_memory(&visited);
	i = 0;
	while (i < game->heightmap)
	{
		visited[i] = malloc(sizeof(int) * game->widthmap);
		if (!visited[i])
		{
			free(visited[i]);
			return (0);
		}
		j = 0;
		while (j < game->widthmap)
		{
			visited[i][j] = 0;
			j++;
		}
		i++;
	}
	return (visited);
}
/*
	Libere mem. des cases visitées
*/
void	free_visited(int **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}
/*
	Verif si map ok en explo. les cases atteignables
*/
void	verify_feasibility(t_game *game)
{
	int	**visited;

	visited = init_visited(game);
	explore_find_player(game);
	explore_map(game, game->player_x, game->player_y, visited);
	explore_complete(game, visited);
	if (!game->exit_found)
	{
		ft_printf("Erreur : Carte impossible\n");
		close_game(game);
	}
	free_visited(visited, game->heightmap);
}