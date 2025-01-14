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

void print_cub_structure(t_cub *cub)
{
    printf("Player:\n");
    printf("  x: %d\n", cub->ply->plyr_x);
    printf("  y: %d\n", cub->ply->plyr_y);
    printf("  angle: %f\n", cub->ply->angle);
    printf("  fov_rd: %f\n", cub->ply->fov_rd);
    printf("  rot: %d\n", cub->ply->rot);
    printf("  l_r: %d\n", cub->ply->l_r);
    printf("  u_d: %d\n", cub->ply->u_d);

    printf("Ray:\n");
    printf("  ray_ngl: %f\n", cub->ray->ray_ngl);
    printf("  distance: %f\n", cub->ray->distance);
    printf("  flag: %d\n", cub->ray->flag);

    printf("Map:\n");
    printf("  p_x: %d\n", cub->map->p_x);
    printf("  p_y: %d\n", cub->map->p_y);
    printf("  w_map: %d\n", cub->map->w_map);
    printf("  h_map: %d\n", cub->map->h_map);

    printf("Config:\n");
    printf("  no_texture: %s\n", cub->config.no_texture);
    printf("  so_texture: %s\n", cub->config.so_texture);
    printf("  we_texture: %s\n", cub->config.we_texture);
    printf("  ea_texture: %s\n", cub->config.ea_texture);
    printf("  floor_color: [%d, %d, %d]\n", cub->config.floor_color[0], cub->config.floor_color[1], cub->config.floor_color[2]);
    printf("  ceiling_color: [%d, %d, %d]\n", cub->config.ceiling_color[0], cub->config.ceiling_color[1], cub->config.ceiling_color[2]);
}

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
