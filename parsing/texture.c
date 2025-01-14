/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguerrer <rguerrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:02:53 by rguerrer          #+#    #+#             */
/*   Updated: 2025/01/14 10:45:48 by rguerrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_get_textures(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map.input[i])
	{
		j = 0;
		while (cub->map.input[i][j] == ' ')
			j++;
		if (ft_strncmp(cub->map.input[i], "NO ", 3) == 0)
			cub->config.no_texture = ft_strdup(&cub->map.input[i][j + 3]);
		else if (ft_strncmp(cub->map.input[i], "SO ", 3) == 0)
			cub->config.so_texture = ft_strdup(&cub->map.input[i][j + 3]);
		else if (ft_strncmp(cub->map.input[i], "WE ", 3) == 0)
			cub->config.we_texture = ft_strdup(&cub->map.input[i][j + 3]);
		else if (ft_strncmp(cub->map.input[i], "EA ", 3) == 0)
			cub->config.ea_texture = ft_strdup(&cub->map.input[i][j + 3]);
		else if (ft_strncmp(cub->map.input[i], "F ", 2) == 0)
		{
			cub->config.floor_color[0] = ft_atoi(&cub->map.input[i][j + 2]);
			cub->config.floor_color[1] = ft_atoi(&cub->map.input[i][j + 5]);
			cub->config.floor_color[2] = ft_atoi(&cub->map.input[i][j + 8]);
		}
		else if (ft_strncmp(cub->map.input[i], "C ", 2) == 0)
		{
			cub->config.ceiling_color[0] = ft_atoi(&cub->map.input[i][j + 2]);
			cub->config.ceiling_color[1] = ft_atoi(&cub->map.input[i][j + 5]);
			cub->config.ceiling_color[2] = ft_atoi(&cub->map.input[i][j + 8]);
		}
		i++;
	}
}

int	ft_parse_textures(t_cub *cub)
{
	ft_get_textures(cub);
	if (!cub->config.no_texture || !cub->config.so_texture ||
		!cub->config.we_texture || !cub->config.ea_texture)
	{
		ft_putstr_fd("Error\nMissing textures\n", 2);
		return (1);
	}
	return (0);
}
