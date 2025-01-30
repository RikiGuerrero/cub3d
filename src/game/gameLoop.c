/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameLoop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjimenez <pjimenez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:29:10 by pjimenez          #+#    #+#             */
/*   Updated: 2025/01/30 11:40:35 by pjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_loop(void *ml)
{
	t_cub	*cub;

	cub = ml;
	mlx_delete_image(cub->mlx_p, cub->img);
	cub->img = mlx_new_image(cub->mlx_p, S_W, S_H);
	hook(cub, 0, 0);
	cast_rays(cub);
	mlx_image_to_window(cub->mlx_p, cub->img, 0, 0);
}

void	init_the_player(t_cub *cub)
{
	cub->ply->plyr_x = (cub->map->p_x * TILE_SIZE) - TILE_SIZE / 2;
	cub->ply->plyr_y = (cub->map->p_y * TILE_SIZE) - TILE_SIZE / 2;
	cub->ply->fov_rd = (FOV * M_PI) / 180;
	if (cub->map->init_view == 'N')
		cub->ply->angle = 3 * M_PI / 2;
	else if (cub->map->init_view == 'S')
		cub->ply->angle = M_PI / 2;
	else if (cub->map->init_view == 'W')
		cub->ply->angle = M_PI;
	else if (cub->map->init_view == 'E')
		cub->ply->angle = 0;
}

void	start_the_game(t_cub *cub)
{
	cub->mlx_p = mlx_init(S_W, S_H, "Cub3D", true);
	init_the_player(cub);
	mlx_loop_hook(cub->mlx_p, &game_loop, cub);
	mlx_key_hook(cub->mlx_p, &mlx_key, cub);
	mlx_loop(cub->mlx_p);
}
