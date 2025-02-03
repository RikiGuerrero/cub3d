/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseCub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguerrer <rguerrer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:13:19 by rguerrer          #+#    #+#             */
/*   Updated: 2025/02/03 16:19:29 by rguerrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_map_rectangular(char **map, int height)
{
	int		max_width;
	int		i;
	int		width;
	char	*new_row;

	max_width = get_max_width(map, height);
	i = 0;
	while (i < height)
	{
		width = ft_strlen(map[i]);
		if (width < max_width)
		{
			new_row = malloc(max_width + 1);
			if (!new_row)
				return ;
			ft_memset(new_row, '1', max_width);
			ft_memcpy(new_row, map[i], width);
			new_row[max_width] = '\0';
			free(map[i]);
			map[i] = new_row;
		}
		i++;
	}
}

void	ft_set_map(t_map *map)
{
	int	i;
	int	j;

	while (map->map[map->h_map] != NULL)
		map->h_map++;
	fill_map_rectangular(map->map, map->h_map);
	while (map->map[0][map->w_map] != '\0')
		map->w_map++;
	i = -1;
	while (++i < map->h_map)
	{
		j = -1;
		while (++j < map->w_map)
		{
			if (ft_strchr("NSWE", map->map[i][j]))
			{
				map->p_x = j + 1;
				map->p_y = i + 1;
				map->init_view = map->map[i][j];
				return ;
			}
		}
	}
}

char	**ft_realloc(char **ptr, size_t old_count, size_t new_count)
{
	char	**new;
	size_t	i;

	new = (char **)malloc(new_count * sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (i < old_count)
	{
		new[i] = ptr[i];
		i++;
	}
	free(ptr);
	return (new);
}

char	**read_file(char *file)
{
	int		fd;
	char	*line;
	char	**map;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nFile not found\n", 2), NULL);
	map = (char **)ft_calloc(1, sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strchr(line, '\r'))
			ft_memmove(ft_strchr(line, '\r'), ft_strchr(line, '\r') + 1,
				ft_strlen(ft_strchr(line, '\r')));
		map = ft_realloc(map, i + 1, i + 2);
		if (!map)
			return (NULL);
		map[i++] = line;
		line = get_next_line(fd);
	}
	return (map[i] = NULL, close(fd), map);
}

int	parse_cub(t_cub *cub, char *file)
{
	init_struct(cub);
	cub->map->input = read_file(file);
	if (!cub->map->input)
		return (free_cub(cub), 1);
	if (ft_check(cub) == 1)
		return (free_cub(cub), 1);
	ft_set_map(cub->map);
	if (ft_parse_textures(cub) == 1)
		return (free_cub(cub), 1);
	return (0);
}
