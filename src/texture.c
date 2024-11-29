/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:15:59 by mg                #+#    #+#             */
/*   Updated: 2024/11/29 10:26:30 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>



char	**read_map(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if(fd < 0)
	{
		ft_printf("[ERREUR] :  CAN'T OPEN FILE ! ");
		return (NULL);
	}

	char	**map;
	char	*line;
	size_t	count_lines;

	map = NULL;
	count_lines = 0;
	while ((line = get_next_line(fd)))
	{
		char	**new_map;
		
		new_map = malloc(sizeof(char *) * (count_lines + 1 + 1));
		if (!new_map)
		{
			ft_printf("[ERREUR] : Mem. alloc");
			close(fd);
			return (NULL);
		}

		size_t	i;
		
		i = 0;
		while(i < count_lines)
		{
			new_map[i] = map[i];
			i++;
		}
	new_map[count_lines] = line;
	new_map[count_lines + 1] = NULL;
	free(map);
	map = new_map;
	count_lines++;
	}

close(fd);
return (map);
}

void	print_map(char	**map)
{
	if(!map)
		return;

	size_t	i;

	i = 0;
	while (map[i])
	{
		ft_printf("%s", map[i]);
		i++;
	}
}



void	player_position(t_game *game)
{
	size_t y;

	y = 0;
	while (game->map[y])
	{
		size_t x;

		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}


void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x + dx;
	new_y =game->player_y +dy;

	if (game->map[new_y][new_x] != '1')
	{
		game->map[game->player_y][game->player_x] = '0';
		game->map[new_y][new_x] = 'P';

		game->player_x = new_x;
		game->player_y = new_y;

		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		draw_map(game->map, game->mlx_ptr, game->win_ptr, game->textures);
	}
}


int	keyboard(int input, t_game *game)
{
	if (input == 13 || input == 0 || input == 1 || input == 2)
	{
		game->input_count++;
		ft_printf("Input :  %d\n", game->input_count);
	}
	if (input == 13)
		move_player(game, 0, -1);
	else if (input == 0)
		move_player(game, -1, 0);
	else if (input == 1)
		move_player(game, 0, 1);
	else if (input == 2)
		move_player(game, 1, 0);
	else if (input == 53)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		free_map(game->map);
		free(game->textures);
		exit (0); // verif si exit ok pour 42
	}
	return (0);
}


void	map_dimension(char	**map, size_t *width, size_t *height)
{
	*width = 0;
	*height = 0;

	while (map[*height])
	{
		size_t line_len;

		line_len = 0;
		while (map[*height][line_len] != '\n') // le 'n' pour skip la colone en trop a droite
			line_len++;
		if (line_len > *width)
			*width = line_len;
		(*height)++;
	}
}

void	free_map(char **map)
{
	size_t	i;

	i = 0;
	while(map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}


void	draw_map(char **map, void *mlx_ptr, void *win_ptr, t_textures *textures)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (map[y])
	{
			x = 0;
		while(map[y][x])
		{
			if (map[y][x] == '1')
				mlx_put_image_to_window(mlx_ptr, win_ptr, textures->wall, x * TILE_SIZE, y * TILE_SIZE);
			else if (map[y][x] == '0')
				mlx_put_image_to_window(mlx_ptr, win_ptr, textures->floor, x * TILE_SIZE, y * TILE_SIZE);
			else if (map[y][x] == 'P')
				mlx_put_image_to_window(mlx_ptr, win_ptr, textures->players, x * TILE_SIZE, y * TILE_SIZE);
			else if (map[y][x] == 'C')
				mlx_put_image_to_window(mlx_ptr, win_ptr, textures->collect, x * TILE_SIZE, y * TILE_SIZE);
				
			x++;
		}
		y++;
	}
}

t_textures	*load_textures(void *mlx_ptr)
{
	t_textures *textures;

	textures = malloc(sizeof(t_textures));
	if (!textures)
		return (NULL);
	
	textures->wall = mlx_xpm_file_to_image(mlx_ptr, "assets/wall.xpm", &textures->width, &textures->height);
	textures->floor = mlx_xpm_file_to_image(mlx_ptr, "assets/background.xpm", &textures->width, &textures->height);
	textures->players = mlx_xpm_file_to_image(mlx_ptr, "assets/players.xpm", &textures->width, &textures->height);
	textures->collect = mlx_xpm_file_to_image(mlx_ptr, "assets/collect.xpm", &textures->width, &textures->height);

	if(!textures->wall || !textures->floor || !textures->players || !textures->collect)
	{
		printf("ERROR : NO LOAD TEXTURE");
		free(textures);
		return (NULL);
	}
	return (textures);
}




int main()
{
	t_game		game;
	size_t 		map_width;
	size_t 		map_height;

	int			window_width;
	int			window_height;

	game.input_count = 0;
	
	game.map = read_map("map/classic.ber");
	if (!game.map)
	{
		printf("[ERROR] -> MAP BROKE");
		return (1);
	}
	else
		printf("[OK] -> MAP");
	


	player_position(&game);



	game.mlx_ptr = mlx_init();
	if (!game.mlx_ptr)
	{
		printf("[ERROR] -> INIT BROKE");
		return (1);
	}
	else
		printf("[OK] -> INIT");



	

	map_dimension(game.map, &map_width, &map_height);
	window_width = map_width * TILE_SIZE;
	window_height = map_height * TILE_SIZE;




	game.win_ptr = mlx_new_window(game.mlx_ptr, window_width, window_height, "test");
	if (!game.win_ptr)
	{
		printf("ERREUR : Impossible de créer la fenêtre\n");
		return (1);
	}


	game.textures = load_textures(game.mlx_ptr);
	if (!game.textures)
	{
		printf("[ERROR] -> LOAD BROKE");
		return (1);
	}
	else
		printf("[OK] -> LOAD");




	draw_map(game.map, game.mlx_ptr, game.win_ptr, game.textures);


	mlx_key_hook(game.win_ptr, keyboard, &game);
	
	mlx_loop(game.mlx_ptr);

	free_map(game.map);
	free(game.textures);

	return 0;
}

