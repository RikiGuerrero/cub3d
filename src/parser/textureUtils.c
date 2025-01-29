/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textureUtils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguerrer <rguerrer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:52:24 by rguerrer          #+#    #+#             */
/*   Updated: 2025/01/29 19:55:21 by rguerrer         ###   ########.fr       */
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

void	ft_load_textures(t_cub *cub)
{
	cub->config.no_texture = mlx_load_png(cub->config.no_texture_path);
	cub->config.so_texture = mlx_load_png(cub->config.so_texture_path);
	cub->config.we_texture = mlx_load_png(cub->config.we_texture_path);
	cub->config.ea_texture = mlx_load_png(cub->config.ea_texture_path);
}
