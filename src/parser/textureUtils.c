/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textureUtils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguerrer <rguerrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:52:24 by rguerrer          #+#    #+#             */
/*   Updated: 2025/01/30 13:43:13 by rguerrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*add_prefix(const char *prefix, const char *path)
{
	char	*full_path;

	full_path = malloc(strlen(prefix) + strlen(path) + 1);
	if (!full_path)
	{
		fprintf(stderr, "Error\nMemory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	strcpy(full_path, prefix);
	strcat(full_path, path);
	return (full_path);
}

int	ft_check_textures(t_cub *cub)
{
	int fd;
	
	if (ft_strcmp(cub->config.no_texture_path + ft_strlen(cub->config.no_texture_path) - 4, ".png") != 0)
		return (1);
	if (ft_strcmp(cub->config.so_texture_path + ft_strlen(cub->config.so_texture_path) - 4, ".png") != 0)
		return (1);
	if (ft_strcmp(cub->config.we_texture_path + ft_strlen(cub->config.we_texture_path) - 4, ".png") != 0)
		return (1);
	if (ft_strcmp(cub->config.ea_texture_path + ft_strlen(cub->config.ea_texture_path) - 4, ".png") != 0)
		return (1);
	fd = open(cub->config.no_texture_path, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	fd = open(cub->config.so_texture_path, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	fd = open(cub->config.we_texture_path, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	fd = open(cub->config.ea_texture_path, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}

void	ft_load_textures(t_cub *cub)
{
	cub->config.no_texture = mlx_load_png(cub->config.no_texture_path);
	cub->config.so_texture = mlx_load_png(cub->config.so_texture_path);
	cub->config.we_texture = mlx_load_png(cub->config.we_texture_path);
	cub->config.ea_texture = mlx_load_png(cub->config.ea_texture_path);
}
