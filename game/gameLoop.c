/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameLoop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjimenez <pjimenez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:29:10 by pjimenez          #+#    #+#             */
/*   Updated: 2025/01/13 23:28:32 by pjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_loop(void *ml)
{
	t_mlx	*mlx;

	mlx = ml;
	mlx_delete_image(mlx->mlx_p, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx_p, S_W, S_H);
	hook(mlx, 0, 0);
	cast_rays(mlx);
	mlx_image_to_window(mlx->mlx_p, mlx->img, 0, 0);
}

void init_the_player(t_mlx mlx)
{
	mlx.ply->plyr_x = mlx.dt->p_x * TILE_SIZE + TILE_SIZE / 2;
	mlx.ply->plyr_y = mlx.dt->p_y * TILE_SIZE + TILE_SIZE / 2;
	mlx.ply->fov_rd = (FOV * M_PI) / 180;
	mlx.ply->angle = M_PI;

}

void	start_the_game(t_data *dt)
{
	t_mlx	mlx;

	mlx.dt = dt;
	mlx.ply = calloc(1, sizeof(t_player));
	mlx.ray = calloc(1, sizeof(t_ray));
	mlx.mlx_p = mlx_init(S_W, S_H, "Cub3D", 0);
	init_the_player(mlx);
	mlx_loop_hook(mlx.mlx_p, &game_loop, &mlx);
	mlx_key_hook(mlx.mlx_p, &mlx_key, &mlx);
	mlx_loop(mlx.mlx_p);
}