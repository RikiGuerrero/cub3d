/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguerrer <rguerrer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:03:59 by rguerrer          #+#    #+#             */
/*   Updated: 2025/02/02 15:57:59 by rguerrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strange_chars(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		if (map[i][0] == '\0')
			return (ft_putstr_fd("Error\nEmpty line in the map\n", 2), 1);
		j = -1;
		while (map[i][++j])
		{
			if (!ft_strchr(" 10\nNSWE ", map[i][j]))
				return (ft_putstr_fd
					("Error\nStrange characters in the map\n", 2), 1);
		}
		i++;
	}
	return (0);
}

int	ft_check_walls(char **map)
{
	int	i;
	int	j;
	int	lines;

	i = -1;
	lines = ft_count_lines(map);
	while (map[++i])
	{
		j = 0;
		while (map[i][j] && map[i][j] == ' ')
			j++;
		if (map[i][j] != '1' || map[i][ft_strlen(map[i]) - 1] != '1')
			return (ft_putstr_fd("Error\nMap is not surrounded\n", 2), 1);
		if (i == 0 || i == lines - 1)
		{
			while (map[i][j])
			{
				if (!ft_strchr("1 \n", map[i][j]))
					return (ft_putstr_fd
						("Error\nMap is not surrounded by walls\n", 2), 1);
				j++;
			}
		}
	}
	return (0);
}

int	ft_check_double(char **map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' ||
				map[i][j] == 'W')
				count++;
			if (count > 1)
				return (ft_putstr_fd("Error\nMore than one player\n", 2), 1);
			j++;
		}
		i++;
	}
	if (count == 0)
		return (ft_putstr_fd("Error\nNo player\n", 2), 1);
	return (0);
}

int	ft_check_unclosed(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (ft_strchr("0WNSE", map[i][j]))
			{
				if (map[i][j + 1] == '\0' || map[i][j - 1] == '\0' ||
					map[i + 1][j] == '\0' || map[i - 1][j] == '\0')
					return (ft_putstr_fd("Error\nMap not closed\n", 2), 1);
				else if (map[i][j + 1] == ' ' || map[i][j - 1] == ' ' ||
					map[i + 1][j] == ' ' || map[i - 1][j] == ' ')
					return (ft_putstr_fd("Error\nMap not closed\n", 2), 1);
			}
		}
	}
	return (0);
}

int	ft_check_map(char **map)
{
	if (ft_strange_chars(map) == 1)
		return (1);
	if (ft_check_walls(map) == 1)
		return (1);
	if (ft_check_unclosed(map) == 1)
		return (1);
	if (ft_check_double(map) == 1)
		return (1);
	return (0);
}
