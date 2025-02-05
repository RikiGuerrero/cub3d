/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textureUtils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguerrer <rguerrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:52:24 by rguerrer          #+#    #+#             */
/*   Updated: 2025/02/05 12:02:45 by rguerrer         ###   ########.fr       */
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

int	ft_check_texture_ext(char *path)
{
	if (ft_strcmp(path + ft_strlen(path) - 4, ".png") != 0)
		return (1);
	return (0);
}

int	ft_check_texture_file(char *path)
{
	int		fd;
	uint8_t	buffer[8];

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	if (read(fd, buffer, 8) != 8)
	{
		close(fd);
		return (1);
	}
	close(fd);
	if (ft_memcmp(buffer, "\x89PNG\r\n\x1a\n", 8) != 0)
		return (1);
	return (0);
}

int	ft_check_textures(t_cub *cub)
{
	if (ft_check_texture_ext(cub->config.no_texture_path)
		|| ft_check_texture_ext(cub->config.so_texture_path)
		|| ft_check_texture_ext(cub->config.we_texture_path)
		|| ft_check_texture_ext(cub->config.ea_texture_path))
		return (1);
	if (ft_check_texture_file(cub->config.no_texture_path)
		|| ft_check_texture_file(cub->config.so_texture_path)
		|| ft_check_texture_file(cub->config.we_texture_path)
		|| ft_check_texture_file(cub->config.ea_texture_path))
		return (1);
	return (0);
}

void	ft_load_textures(t_cub *cub)
{
	cub->config.no_texture = mlx_load_png(cub->config.no_texture_path);
	cub->config.so_texture = mlx_load_png(cub->config.so_texture_path);
	cub->config.we_texture = mlx_load_png(cub->config.we_texture_path);
	cub->config.ea_texture = mlx_load_png(cub->config.ea_texture_path);
}
