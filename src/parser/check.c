/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguerrer <rguerrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:00:25 by rguerrer          #+#    #+#             */
/*   Updated: 2025/01/30 12:36:38 by rguerrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			ft_strstr(input[i], "NO") == NULL &&
			ft_strstr(input[i], "SO") == NULL &&
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

int	ft_valid_elements(char **input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (ft_strstr("NO", input[i]) == 0
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
	char	**rgb;

	i = -1;
	while (input[++i])
	{
		j = 0;
		while (input[i][j] == ' ')
			j++;
		if (ft_strchr("FC", input[i][j]))
		{
			rgb = ft_split(&input[i][++j], ',');
			if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
				return (ft_putstr_fd("Error\nInvalid RGB format\n", 2),
					ft_free_split(rgb), 1);
			if (!ft_is_valid_number(rgb[0]) || !ft_is_valid_number(rgb[1])
				|| !ft_is_valid_number(rgb[2]))
				return (ft_putstr_fd("Error\nRGB values out of range\n", 2),
					ft_free_split(rgb), 1);
			ft_free_split(rgb);
		}
	}
	return (0);
}

int	ft_check(t_cub *cub)
{
	if (ft_valid_elements(cub->map->input) == 1)
		return (1);
	if (ft_valid_rgb(cub->map->input) == 1)
		return (1);
	cub->map->map = ft_map(cub->map->input);
	if (!cub->map->map)
		return (1);
	ft_quit_newline(cub->map->map);
	if (ft_check_map(cub->map->map) == 1)
		return (1);
	return (0);
}
