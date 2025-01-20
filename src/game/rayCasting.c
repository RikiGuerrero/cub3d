/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayCasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjimenez <pjimenez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:28:54 by pjimenez          #+#    #+#             */
/*   Updated: 2025/01/20 13:49:21 by pjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float get_h_inter(t_cub *cub, float angl)
{
	float h_y;
	float h_x;
	float x_step;
	float y_step;
	int pixel;
	t_player *ply;

	ply = cub->ply;
	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angl);
	h_y = floor(ply->plyr_y / TILE_SIZE) * TILE_SIZE;
	h_x = ply->plyr_x + (h_y - ply->plyr_y) / tan(angl);
}

void cast_rays(t_cub *cub)
{
	double h_inter;
	double v_inter;
	int ray;

	ray = 0;
	cub->ray->ray_ngl = cub->ply->angle - (cub->ply->fov_rd / 2); //(pi/2) -(fov_rd/2)

	while (S_W > ray) //crea rayos hasta que se complete el width de la pantalla
	{
		h_inter = get_h_inter(cub, cub->ray->ray_ngl); //obtiene la interseccion horizontal
		
		ray++;
		cub->ray->ray_ngl += (cub->ply->fov_rd / S_W); //incrementa el angulo de los rayos
	}
}