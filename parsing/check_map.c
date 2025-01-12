/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguerrer <rguerrer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:03:59 by rguerrer          #+#    #+#             */
/*   Updated: 2025/01/11 14:03:59 by rguerrer         ###   ########.fr       */
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
		j = 0;
		if (map[i][j] == '\0')
		{
			ft_putstr_fd("Error\nEmpty line in the map\n", 2);
			return (1);
		}
		while (map[i][j])
		{
			if (map[i][j] != ' ' && map[i][j] != '1' && map[i][j] != '0' &&
				map[i][j] != '2' && map[i][j] != 'N' && map[i][j] != 'S' &&
				map[i][j] != 'E' && map[i][j] != 'W' && map[i][j] != '\n')
			{
				ft_putstr_fd("Error\nStrange characters in the map\n", 2);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_count_lines(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	ft_check_walls(char **map)
{
	int	i;
	int	j;
	int	lines;

	i = 0;
	lines = ft_count_lines(map);
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] == ' ')
			j++;
		if (map[i][j] != '1' || map[i][ft_strlen(map[i]) - 2] != '1') // -2 para evitar el \n
		{
			ft_putstr_fd("Error\nMap is not surrounded by walls\n", 2);
			return (1);
		}
		if (i == 0 || i == lines - 1)
		{
			while (map[i][j])
			{
				if (map[i][j] != '1' && map[i][j] != ' ' && map[i][j] != '\n')
				{
					ft_putstr_fd("Error\nMap is not surrounded by walls\n", 2);
					return (1);
				}
				j++;
			}
		}
		i++;
	}
	return (0);
}

int	ft_check_double(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' ||
				map[i][j] == 'W')
			{
				if (map[i][j + 1] == 'N' || map[i][j + 1] == 'S' ||
					map[i][j + 1] == 'E' || map[i][j + 1] == 'W')
				{
					ft_putstr_fd("Error\nDouble player position\n", 2);
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_check_unclosed(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == '2' || map[i][j] == 'N' ||
				map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (map[i][j + 1] == '\0' || map[i][j - 1] == '\0' ||
					map[i + 1][j] == '\0' || map[i - 1][j] == '\0')
				{
					ft_putstr_fd("Error\nMap not closed\n", 2);
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_valid_map(char **map)
{
	if (ft_strange_chars(map) == 1)
		return (1);	
	if (ft_check_unclosed(map) == 1)
		return (1);
	if (ft_check_walls(map) == 1)
		return (1);
	if (ft_check_double(map) == 1)
		return (1);
	return (0);
}