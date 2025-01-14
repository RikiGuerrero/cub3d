/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguerrer <rguerrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:00:25 by rguerrer          #+#    #+#             */
/*   Updated: 2025/01/14 12:42:11 by rguerrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_quit_newline(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '\n')
				map[i][j] = '\0';
			j++;
		}
		i++;
	}
}

int	ft_valid_elements(char **input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (ft_strncmp(input[i], "NO ", 3) == 0
			|| ft_strncmp(input[i], "SO ", 3) == 0
			|| ft_strncmp(input[i], "WE ", 3) == 0
			|| ft_strncmp(input[i], "EA ", 3) == 0
			|| ft_strncmp(input[i], "F ", 2) == 0
			|| ft_strncmp(input[i], "C ", 2) == 0)
			count++;
		else if (input[i][0] != '\n' && count != 6)
		{
			ft_putstr_fd("Error\nMissing elements\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_is_valid_number(const char *str)
{
	int	num;

	num = atoi(str);
	return (num >= 0 && num <= 255);
}

int	ft_valid_rgb(char **input)
{
	int		i;
	int		j;
	char	**rgb_values;

	i = 0;
	while (input[i])
	{
		j = 0;
		while (input[i][j] == ' ')
			j++;
		if (input[i][j] == 'F' || input[i][j] == 'C')
		{
			j++;
			while (input[i][j] == ' ')
				j++;
			rgb_values = ft_split(&input[i][j], ',');
			if (!rgb_values || !rgb_values[0] || !rgb_values[1] || !rgb_values[2] || rgb_values[3])
			{
				ft_putstr_fd("Error\nInvalid RGB format\n", 2);
				return (1);
			}
			if (!ft_is_valid_number(rgb_values[0]) || !ft_is_valid_number(rgb_values[1]) || !ft_is_valid_number(rgb_values[2]))
			{
				ft_putstr_fd("Error\nRGB values out of range\n", 2);
				return (1);
			}
			//ft_free_split(rgb_values);
		}
		i++;
	}
	return (0);
}
int	ft_checks(t_cub *cub)
{
	if (ft_valid_elements(cub->map->input) == 1)
		return (1);
	if (ft_valid_rgb(cub->map->input) == 1)
		return (1);
	cub->map->map = ft_map(cub->map->input);
	if (!cub->map->map)
		return (1);
	ft_quit_newline(cub->map->map);
	if (ft_valid_map(cub->map->map) == 1)
		return (1);
	ft_set_map(cub->map);
	return (0);
}
