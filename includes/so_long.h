/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:38:43 by mg                #+#    #+#             */
/*   Updated: 2024/12/05 13:53:43 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "../mlx/mlx.h"
#include "get_next_line.h"
#include "ft_printf.h"

#define TILE_SIZE 32

typedef struct s_textures
{
	void	*wall;
	void	*floor;
	void	*players;
	void	*collect;
	void	*exit;
	int		width;
	int		height;
}			t_textures;

typedef	struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**map;
	t_textures	*textures;
	int			player_x;
	int			player_y;
	int			input_count;
	int			count_collect;
	int			total_collect;
	size_t		widthmap;
	size_t		heightmap;
}				t_game;

char	**read_map(const char *path);


int			keyboard(int input, t_game *game);
int			close_game(t_game *game);
int			move_player(t_game *game, int dx, int dy);
int			move_player(t_game *game, int dx, int dy);
void		game_end(t_game *game, int new_x, int new_y);
int			update_position(t_game *game, int new_x, int new_y);
void		collect_item(t_game *game, int new_x, int new_y);

void		count_collect(char **map, t_game *game);
void		cleanup(t_game *game);
void		print_map(char **map);
void		player_position(t_game *game);
void		map_dimension(char **map, t_game *game);
void		free_map(char **map);
void		draw_tile(t_game *game, char tile, int x, int y);
void		draw_map(t_game *game);
void		check_errors(t_game *game);

void		verify_feasibility(t_game *game);
int			**init_visited(size_t width, size_t height);
void		free_visited(int **visited, size_t height);
void		dfs_explore(t_game *game, int y, int x, int **visited, size_t width, size_t height);
t_textures 	*load_textures(void *mlx_ptr);

#endif