/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magillie <magillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:15:54 by prossi            #+#    #+#             */
/*   Updated: 2024/12/14 14:02:25 by magillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "get_next_line.h"
# include "ft_printf.h"
# include "../minilibx/mlx.h"

typedef struct s_game
{
	int		fd;
	int		i;
	int		j;
	int		heightmap;
	int		widthmap;
	int 	h;
	int 	w;

	int		exit_open;
	int		player_found;
	int		exit_found;
	int		collectabled;
	int		player_x;
	int		player_y;
	int		exit_x;
	int		exit_y;
	int		**visited;

	int		nbr_player;
	int		nbr_collect;
	int		nbr_exit;
	int		x_axis;
	int		y_axis;
	int		counter;
	int		collectibles;

	char	**map;

	void	*floor;
	void	*wall;
	void	*player;
	void	*exit;
	void	*collect;
	void	*mlx_ptr;
	void	*win_ptr;

}	t_game;

int		close_game(t_game *game);
int		map_reading(t_game *game, char **argv);
void	put_texture(t_game *game);
void	place_images_in_game(t_game *game);
void	check_errors(t_game *game);
void	explore_find_player(t_game *game);
void	explore_map(t_game *game, int x, int y, int **visited);
void	explore_complete(t_game *game, int **visited);
int		*free_int_memory(int ***ptr);
void	free_visited(int **visited, int height);
void	explore_find_exit(t_game *game, int i, int j, int **visited);
void	verify_feasibility(t_game *game);

void	is_collect(t_game *game, int height, int width);
void	is_player(t_game *game, int height, int width);
void	set_texture(t_game *game);
int		read_the_map(t_game *game, char **argv);
int		check_control(int input, t_game *game);
void	*ft_memset(void *b, int c, size_t length);
void	verify_feasibility(t_game *game);

#endif