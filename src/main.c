/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguerrer <rguerrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:45:56 by rguerrer          #+#    #+#             */
/*   Updated: 2025/01/28 12:28:42 by rguerrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_config(t_config *config)
{
	free(config->no_texture_path);
	free(config->so_texture_path);
	free(config->we_texture_path);
	free(config->ea_texture_path);
	free(config->no_texture);
	free(config->so_texture);
	free(config->we_texture);
	free(config->ea_texture);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->input[i])
		free(map->input[i++]);
	free(map->input);
}

void	free_cub(t_cub *cub)
{
	free_config(&cub->config);
	if (cub->map->input)
		free_map(cub->map);
	free(cub->map);
	free(cub->ply);
	free(cub->ray);
}

void	ft_exit(t_cub *cub)
{
	free_cub(cub);
	mlx_delete_image(cub->mlx_p, cub->img);
	mlx_close_window(cub->mlx_p);
	mlx_terminate(cub->mlx_p);
	printf("Game closed\n");
	exit(0);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac != 2 || ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4))
	{
		ft_putstr_fd("Error\nInvalid arguments\n", 2);
		return (1);
	}
	else
	{
		if (parse_cub(&cub, av[1]) == 1)
			return (1);
		printf("Running game\n");
		start_the_game(&cub);
		printf("Game over\n");
	}
	return (0);
}
