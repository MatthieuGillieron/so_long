/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:15:59 by mg                #+#    #+#             */
/*   Updated: 2024/11/26 13:28:02 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "../mlx/mlx.h"
#include "../includes/get_next_line.h"
#include "../includes/ft_printf.h"

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
	void		*mlx_ptr;
	void		*win_ptr;
	char		**map;
	t_textures	*textures;
	

	map = read_map("map/map1.ber");
	if (!map)
	{
		printf("[ERROR] -> MAP BROKE");
		return (1);
	}
	else
		printf("[OK] -> MAP");



	mlx_ptr = mlx_init();
	if (!mlx_ptr)
	{
		printf("[ERROR] -> INIT BROKE");
		return (1);
	}
	else
		printf("[OK] -> INIT");

	

	win_ptr = mlx_new_window(mlx_ptr, 600, 500, "test");
	if (!win_ptr)
	{
		printf("ERREUR : Impossible de créer la fenêtre\n");
		return (1);
	}



	textures = load_textures(mlx_ptr);
	if (!textures)
	{
		printf("[ERROR] -> LOAD BROKE");
		return (1);
	}
	else
		printf("[OK] -> LOAD");


	draw_map(map, mlx_ptr, win_ptr, textures);
	
	mlx_loop(mlx_ptr);
	return 0;
}

