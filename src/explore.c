#include "../includes/so_long.h"

static int	is_valid_position(t_game *game, int x, int y, int **visited)
{
	int	is_within_map_bounds;
	int	is_not_wall;
	int	is_exit_open;
	int	has_not_been_visited;

	is_within_map_bounds = (x >= 0 && x < game->widthmap && y >= 0 \
			&& y < game->heightmap);
	is_not_wall = (game->map[y][x] != '1');
	is_exit_open = (game->map[y][x] != 'E' || game->exit_open);
	has_not_been_visited = (!visited[y][x]);
	return ((is_within_map_bounds && is_not_wall && is_exit_open \
			&& has_not_been_visited));
}


void	explore_find_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->heightmap && !game->player_found)
	{
		j = 0;
		while (j < game->widthmap)
		{
			if (game->map[i][j] == 'P')
			{
				game->player_x = j;
				game->player_y = i;
				game->player_found = 1;
				break ;
			}
			j++;
		}
		i++;
	}
}




void	explore_find_exit(t_game *game, int i, int j, int **visited)
{
	while (i < game->heightmap && !game->exit_found)
	{
		j = 0;
		while (j < game->widthmap)
		{
			if (game->map[i][j] == 'E' && visited[i][j])
			{
				game->exit_found = 1;
				break ;
			}
			j++;
		}
		i++;
	}
}




void	explore_complete(t_game *game, int **visited)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (game->collectabled == game->nbr_collect)
	{
		i = 0;
		while (i < game->heightmap)
		{
			j = 0;
			while (j < game->widthmap)
			{
				visited[i][j] = 0;
				j++;
			}
			i++;
		}
		game->exit_open = 1;
		explore_map(game, game->player_x, game->player_y, visited);
	}
	i = 0;
	explore_find_exit(game, i, j, visited);
}

void	explore_map(t_game *game, int x, int y, int **visited)
{
	if (!is_valid_position(game, x, y, visited))
	{
		return ;
	}
	visited [y][x] = 1;
	if (game->map[y][x] == 'C')
		(game->collectabled)++;
	explore_map(game, x + 1, y, visited);
	explore_map(game, x - 1, y, visited);
	explore_map(game, x, y + 1, visited);
	explore_map(game, x, y - 1, visited);
}

