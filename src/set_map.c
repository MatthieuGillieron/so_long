/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:28:26 by mg                #+#    #+#             */
/*   Updated: 2024/12/05 13:05:24 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

char	**read_map(const char *path)
{
	int	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_printf("ERROR : Can't open fd ! \n"), NULL);
	char	*line;
	char	**map;
	size_t	count_lines;

	map = NULL;
	count_lines = 0;
	while ((line = get_next_line(fd)))
	{
		char	**new_map;

		new_map = malloc(sizeof(char *) * (count_lines + 2));
		if(!new_map)
			return (close(fd), ft_printf("ERROR : Alloc. mem failed \n"), NULL);
		size_t	i;

		i = 0;
		while (i < count_lines)
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

void	free_map(char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	map_dimension(char **map, t_game *game)
{
	game->widthmap = 0;
	game->heightmap = 0;
	while (map[game->heightmap])
	{
		size_t	line_len;

		line_len = 0;
		while (map[game->heightmap][line_len]
		 && map[game->heightmap][line_len] != '\n')
			line_len++;
		if (line_len > game->widthmap)
			game->widthmap = line_len;
		game->heightmap++;
	}
}



int	close_game(t_game *game)
{
	cleanup(game);
	exit(0);
	return (0);
}
