/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayCasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjimenez <pjimenez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:28:54 by pjimenez          #+#    #+#             */
/*   Updated: 2025/01/28 12:18:32 by pjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	get_h_inter(t_cub *cub, float angl)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angl);
	h_y = floor(cub->ply->plyr_y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &h_y, &y_step, 1);
	h_x = cub->ply->plyr_x + (h_y - cub->ply->plyr_y) / tan(angl);
	if ((unit_circle(angl, 'y') && x_step > 0)
		|| (!unit_circle(angl, 'y') && x_step < 0))
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, cub))
	{
		h_x += x_step;
		h_y += y_step;
	}
	cub->ray->hor_x = h_x;
	return (sqrt(pow(h_x - cub->ply->plyr_x, 2)
			+ pow(h_y - cub->ply->plyr_y, 2)));
}

float	get_v_inter(t_cub *cub, float angl)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angl);
	v_x = floor(cub->ply->plyr_x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &v_x, &x_step, 0);
	v_y = cub->ply->plyr_y + (v_x - cub->ply->plyr_x) * tan(angl);
	if ((unit_circle(angl, 'x') && y_step < 0)
		|| (!unit_circle(angl, 'x') && y_step > 0))
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, cub))
	{
		v_x += x_step;
		v_y += y_step;
	}
	cub->ray->ver_y = v_y;
	return (sqrt(pow(v_x - cub->ply->plyr_x, 2)
			+ pow(v_y - cub->ply->plyr_y, 2)));
}

void	cast_rays(t_cub *cub)
{
	double	h_inter;
	double	v_inter;
	int		ray;

	ray = 0;
	cub->ray->ray_ngl = cub->ply->angle - (cub->ply->fov_rd / 2);
	while (ray < S_W)
	{
		cub->ray->flag = 0;
		h_inter = get_h_inter(cub, nor_angle(cub->ray->ray_ngl));
		v_inter = get_v_inter(cub, nor_angle(cub->ray->ray_ngl));
		if (v_inter <= h_inter)
			cub->ray->distance = v_inter;
		else
		{
			cub->ray->distance = h_inter;
			cub->ray->flag = 1;
		}
		render_wall(cub, ray);
		ray++;
		cub->ray->ray_ngl += (cub->ply->fov_rd / S_W);
	}
}
