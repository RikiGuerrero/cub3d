/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameLoop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguerrer <rguerrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:29:10 by pjimenez          #+#    #+#             */
/*   Updated: 2025/01/14 13:20:49 by rguerrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_loop(void *ml)
{
	t_cub	*mlx;

	mlx = ml;
	mlx_delete_image(mlx->mlx_p, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx_p, S_W, S_H);
	hook(mlx, 0, 0);
	cast_rays(mlx);
	mlx_image_to_window(mlx->mlx_p, mlx->img, 0, 0);
}

void init_the_player(t_cub *mlx)
{
	mlx->ply->plyr_x = mlx->map->p_x * TILE_SIZE + TILE_SIZE / 2;
	mlx->ply->plyr_y = mlx->map->p_y * TILE_SIZE + TILE_SIZE / 2;
	mlx->ply->fov_rd = (FOV * M_PI) / 180;
	mlx->ply->angle = M_PI;

}

void	start_the_game(t_cub *cub)
{
	cub->ply = calloc(1, sizeof(t_player));
	cub->ray = calloc(1, sizeof(t_ray));
	cub->mlx_p = mlx_init(S_W, S_H, "Cub3D", 0);
	init_the_player(cub);
	mlx_loop_hook(cub->mlx_p, &game_loop, cub);
	mlx_key_hook(cub->mlx_p, &mlx_key, cub);
	mlx_loop(cub->mlx_p);
}
