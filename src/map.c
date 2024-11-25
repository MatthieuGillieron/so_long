/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:15:59 by mg                #+#    #+#             */
/*   Updated: 2024/11/25 11:51:13 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
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
