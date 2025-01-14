/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguerrer <rguerrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:13:19 by rguerrer          #+#    #+#             */
/*   Updated: 2025/01/14 10:45:38 by rguerrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	{
		ft_putstr_fd("Error\nFile not found\n", 2);
		return (NULL);
	}
	map = (char **)ft_calloc(1, sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		char *cr = strchr(line, '\r');
		if (cr)
			memmove(cr, cr + 1, strlen(cr));
		map = ft_realloc(map, i + 1, i + 2); // lineas para eliminar \r
		if (!map)
			return (NULL);
		map[i] = line;
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

char	**ft_map(char **input)
{
	int		i;
	int		j;

	i = 0;
	while (input[i])
	{
		j = 0;
		while (input[i][j] == ' ')
			j++;
		if (input[i][j] && input[i][j] != '\n' &&
			ft_strncmp(input[i], "NO ", 3) != 0 &&
			ft_strncmp(input[i], "SO ", 3) != 0 &&
			ft_strncmp(input[i], "WE ", 3) != 0 &&
			ft_strncmp(input[i], "EA ", 3) != 0 &&
			ft_strncmp(input[i], "F ", 2) != 0 &&
			ft_strncmp(input[i], "C ", 2) != 0)
			return (&input[i]);
		i++;
	}
	ft_putstr_fd("Error\nInvalid map\n", 2);
	return (NULL);
}

int	parse_cub(t_cub *cub, char *file)
{
	init_cub(cub);
	cub->map.input = read_file(file);
	if (!cub->map.input)
		return (1);
		//return (ft_delete(cub), 1);
	if (ft_checks(cub) == 1)
		return(1);
		//return (ft_delete(cub), 1);
	if (ft_parse_textures(cub) == 1)
		return (1);
		//return (ft_delete(cub), 1);
	return (0);
}
