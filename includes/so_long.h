/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:38:43 by mg                #+#    #+#             */
/*   Updated: 2024/12/03 13:09:34 by mg               ###   ########.fr       */
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
}				t_game;

char	**read_map(const char *path);

int			keyboard(int input, t_game *game);
int			close_game(t_game *game);

void		cleanup(t_game *game);
void		print_map(char **map);
void		player_position(t_game *game);
int			move_player(t_game *game, int dx, int dy);
void		map_dimension(char **map, size_t *width, size_t *height);
void		free_map(char **map);
void		draw_tile(t_game *game, char tile, int x, int y);
void		draw_map(t_game *game);

t_textures 	*load_textures(void *mlx_ptr);

#endif