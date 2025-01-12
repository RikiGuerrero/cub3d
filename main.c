/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguerrer <rguerrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:45:56 by rguerrer          #+#    #+#             */
/*   Updated: 2024/12/12 11:36:37 by rguerrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
#include <MLX42/MLX42.h>
#include <stdio.h>
#include <stdlib.h>

int32_t main(void)
{
    // Initialize MLX42
    mlx_t* mlx = mlx_init(800, 600, "MLX42 Window", true);
    if (!mlx)
    {
        fprintf(stderr, "MLX42 initialization failed\n");
        return EXIT_FAILURE;
    }

    // Create a new image
    mlx_image_t* img = mlx_new_image(mlx, 800, 600);
    if (!img)
    {
        fprintf(stderr, "Image creation failed\n");
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    // Set the image to the window
    mlx_image_to_window(mlx, img, 0, 0);

    // Main loop
    mlx_loop(mlx);

    // Cleanup
    mlx_delete_image(mlx, img);
    mlx_terminate(mlx);

    return EXIT_SUCCESS;
}
*/
int main(int ac, char **av)
{
	t_cub cub;

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
		//game_loop(&map);
		printf("Game over\n");
	}
	return (0);
}
