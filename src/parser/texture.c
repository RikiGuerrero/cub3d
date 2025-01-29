/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguerrer <rguerrer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:02:53 by rguerrer          #+#    #+#             */
/*   Updated: 2025/01/29 19:55:35 by rguerrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_parse_texture(char *line, char **texture_path, int offset)
{
	*texture_path = ft_strdup(&line[offset]);
	*texture_path = add_prefix("./", *texture_path);
	remove_non_printable(*texture_path);
}

void	ft_parse_color(char *line, int *color)
{
	char	**colors;

	colors = ft_split(line, ',');
	if (colors)
	{
		color[0] = ft_atoi(colors[0]);
		color[1] = ft_atoi(colors[1]);
		color[2] = ft_atoi(colors[2]);
		free(colors[0]);
		free(colors[1]);
		free(colors[2]);
		free(colors);
	}
}

void	ft_parse_texture_line(char *line, t_cub *cub, int j)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		ft_parse_texture(line, &cub->config.no_texture_path, j + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		ft_parse_texture(line, &cub->config.so_texture_path, j + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		ft_parse_texture(line, &cub->config.we_texture_path, j + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		ft_parse_texture(line, &cub->config.ea_texture_path, j + 3);
	else if (ft_strncmp(line, "F ", 2) == 0)
		ft_parse_color(&line[2], cub->config.floor_color);
	else if (ft_strncmp(line, "C ", 2) == 0)
		ft_parse_color(&line[2], cub->config.ceiling_color);
}

void	ft_get_textures(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (cub->map->input[++i])
	{
		j = 0;
		while (cub->map->input[i][j] == ' ')
			j++;
		ft_parse_texture_line(cub->map->input[i], cub, j);
	}
	ft_load_textures(cub);
}

int	ft_parse_textures(t_cub *cub)
{
	ft_get_textures(cub);
	if (!cub->config.no_texture || !cub->config.so_texture
		|| !cub->config.we_texture || !cub->config.ea_texture)
	{
		ft_putstr_fd("Error\nMissing textures\n", 2);
		return (1);
	}
	return (0);
}
