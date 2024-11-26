/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:15:59 by mg                #+#    #+#             */
/*   Updated: 2024/11/26 09:34:09 by mg               ###   ########.fr       */
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


void	draw_map(char **map, void *mlx_ptr, void *win_ptr)
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
				mlx_pixel_put(mlx_ptr, win_ptr, x * TILE_SIZE, y * TILE_SIZE, 0xFFFFFFF);
			else if (map[y][x] == '0')
				mlx_pixel_put(mlx_ptr, win_ptr, x * TILE_SIZE, y * TILE_SIZE, 0x000000);
			else if (map[y][x] == 'P')
				mlx_pixel_put(mlx_ptr, win_ptr, x * TILE_SIZE, y * TILE_SIZE, 0xFF0000);
			else if (map[y][x] == 'C')
				mlx_pixel_put(mlx_ptr, win_ptr, x * TILE_SIZE, y * TILE_SIZE, 0x00FF00);
				
			x++;
		}
		y++;
	}
}






int main()
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;

	map = read_map("map/map1.ber");
	if (!map)
	{
		printf(" ERREUR : NO LOAD MAP");
		return (1);
	}

	printf("avant init\n");
	mlx_ptr = mlx_init();
	printf("after init\n");

	if (!mlx_ptr)
	{
		printf("ERREUR : INIT IS BROKE");
		return (1);
	}

	printf("before win\n");
	win_ptr = mlx_new_window(mlx_ptr, 800, 600, "its so long");
	printf("after win\n");

	if (!win_ptr)
	{
		printf("ERREUR : BROKE WINDOW");
		return (1);
	}
	else
		printf("\nwindow ok\n");
		
	draw_map(map, mlx_ptr, win_ptr);

	printf("\nbefore loop\n");
	mlx_loop(mlx_ptr);
	printf("after loop\n");

	size_t	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}

	free(map);
	return 0;
}









/*
int	main()
{
	char	**map;

	map = read_map("map/map1.ber");
	if (!map)
	{
		ft_printf("ERREUR : map no charge");
		return (1);
	}
	ft_printf("OK : map charge");
	print_map(map);

	size_t	i;
	
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	
	free(map);
	return (0);
}
*/
