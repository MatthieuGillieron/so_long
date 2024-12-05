/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:42:32 by mg                #+#    #+#             */
/*   Updated: 2024/12/05 14:43:09 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int **init_visited( size_t width, size_t height)
{
    int **visited;
	
	visited = malloc(sizeof(int *) * height);
    if (!visited)
        return (NULL);
    size_t y;
	
	y = 0;
    while (y < height)
    {
        visited[y] = malloc(sizeof(int) * width);
        if (!visited[y])
        {
            free_visited(visited, y);
            return (NULL);
        }
        size_t x;
		
		x = 0;
        while (x < width)
            visited[y][x++] = 0;
        y++;
    }
    return (visited);
}

// Libère la mémoire allouée pour la matrice visitée
void free_visited(int **visited, size_t height)
{
    size_t y = 0;
    while (y < height)
    {
        free(visited[y]);
        y++;
    }
    free(visited);
}

// Parcours DFS de la carte
void dfs_explore(t_game *game, int y, int x, int **visited, size_t width, size_t height)
{
    if (y < 0 || x < 0 || y >= (int)height || x >= (int)width || visited[y][x] || game->map[y][x] == '1')
        return;
    visited[y][x] = 1;

    dfs_explore(game, y + 1, x, visited, width, height);
    dfs_explore(game, y - 1, x, visited, width, height);
    dfs_explore(game, y, x + 1, visited, width, height);
    dfs_explore(game, y, x - 1, visited, width, height);
}


// Vérifie si la carte est faisable
void verify_feasibility(t_game *game)
{
    int **visited;

  	visited = init_visited(game->widthmap, game->heightmap);
    if (!visited)
    {
        ft_printf("Erreur : allocation mémoire\n");
        close_game(game);
    }

    dfs_explore(game, game->player_y, game->player_x, visited, game->widthmap, game->heightmap);

    free_visited(visited, game->heightmap);  // Libération de la mémoire après l'exploration
}