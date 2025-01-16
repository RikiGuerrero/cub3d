/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguerrer <rguerrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:02:53 by rguerrer          #+#    #+#             */
/*   Updated: 2025/01/14 12:23:47 by rguerrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *add_prefix(const char *prefix, const char *path)
{
	char *full_path = malloc(strlen(prefix) + strlen(path) + 1);
	if (!full_path)
	{
    	fprintf(stderr, "Error\nMemory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	strcpy(full_path, prefix);
	strcat(full_path, path);
	return full_path;
}

void remove_non_printable(char *str)
{
    char *src = str, *dst = str;
    while (*src)
    {
        if (*src >= 32 && *src <= 126)
        {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

void	ft_get_textures(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map->input[i])
	{
		j = 0;
		while (cub->map->input[i][j] == ' ')
			j++;
		if (ft_strncmp(cub->map->input[i], "NO ", 3) == 0)
			cub->config.no_texture_path = ft_strdup(&cub->map->input[i][j + 3]);
		else if (ft_strncmp(cub->map->input[i], "SO ", 3) == 0)
			cub->config.so_texture_path = ft_strdup(&cub->map->input[i][j + 3]);
		else if (ft_strncmp(cub->map->input[i], "WE ", 3) == 0)
			cub->config.we_texture_path = ft_strdup(&cub->map->input[i][j + 3]);
		else if (ft_strncmp(cub->map->input[i], "EA ", 3) == 0)
			cub->config.ea_texture_path = ft_strdup(&cub->map->input[i][j + 3]);
		else if (ft_strncmp(cub->map->input[i], "F ", 2) == 0)
		{
			cub->config.floor_color[0] = ft_atoi(&cub->map->input[i][j + 2]);
			cub->config.floor_color[1] = ft_atoi(&cub->map->input[i][j + 5]);
			cub->config.floor_color[2] = ft_atoi(&cub->map->input[i][j + 8]);
		}
		else if (ft_strncmp(cub->map->input[i], "C ", 2) == 0)
		{
			cub->config.ceiling_color[0] = ft_atoi(&cub->map->input[i][j + 2]);
			cub->config.ceiling_color[1] = ft_atoi(&cub->map->input[i][j + 5]);
			cub->config.ceiling_color[2] = ft_atoi(&cub->map->input[i][j + 8]);
		}
		i++;
	}

	 // Añadir prefijo "./" a las rutas de textura
    cub->config.no_texture_path = add_prefix("./", cub->config.no_texture_path);
	cub->config.so_texture_path = add_prefix("./", cub->config.so_texture_path);
	cub->config.we_texture_path = add_prefix("./", cub->config.we_texture_path);
	cub->config.ea_texture_path = add_prefix("./", cub->config.ea_texture_path);

	remove_non_printable(cub->config.no_texture_path);
    remove_non_printable(cub->config.so_texture_path);
    remove_non_printable(cub->config.we_texture_path);
    remove_non_printable(cub->config.ea_texture_path);

	// Verificar antes si los archivos estan correctos
	// Liberar memoria de las rutas completas


	cub->config.no_texture = mlx_load_png(cub->config.no_texture_path);
	cub->config.so_texture = mlx_load_png(cub->config.so_texture_path);
	cub->config.we_texture = mlx_load_png(cub->config.we_texture_path);
	cub->config.ea_texture = mlx_load_png(cub->config.ea_texture_path);
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
