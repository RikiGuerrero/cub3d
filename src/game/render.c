/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguerrer <rguerrer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:28:04 by pjimenez          #+#    #+#             */
/*   Updated: 2025/02/04 20:06:02 by rguerrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_ceiling(t_cub *mlx, int ray, int t_pix, int b_pix)
{
	int		i;
	int		floor_color;
	int		ceiling_color;

	floor_color = get_rgba(mlx->config.floor_color[0], \
		mlx->config.floor_color[1], \
		mlx->config.floor_color[2], 255);
	ceiling_color = get_rgba(mlx->config.ceiling_color[0], \
		mlx->config.ceiling_color[1], \
		mlx->config.ceiling_color[2], 255);
	i = b_pix;
	while (i < S_H)
		my_mlx_pixel_put(mlx, ray, i++, floor_color);
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(mlx, ray, i++, ceiling_color);
}

mlx_texture_t	*get_texture(t_cub *mlx, int flag)
{
	mlx->ray->ray_ngl = nor_angle(mlx->ray->ray_ngl);
	if (flag == 0)
	{
		if (mlx->ray->ray_ngl > M_PI / 2 && mlx->ray->ray_ngl < 3 * (M_PI / 2))
			return (mlx->config.we_texture);
		else
			return (mlx->config.ea_texture);
	}
	else
	{
		if (mlx->ray->ray_ngl > 0 && mlx->ray->ray_ngl < M_PI)
			return (mlx->config.so_texture);
		else
			return (mlx->config.no_texture);
	}
}

double	get_texture_offset(mlx_texture_t *texture, t_cub *mlx)
{
	double	offset;

	if (mlx->ray->flag == 1)
		offset = fmod(mlx->ray->hor_x, TILE_SIZE)
			* (texture->width / TILE_SIZE);
	else
		offset = fmod(mlx->ray->ver_y, TILE_SIZE)
			* (texture->width / TILE_SIZE);
	if ((mlx->ray->flag == 0 && mlx->ray->ray_ngl > M_PI / 2
			&& mlx->ray->ray_ngl < 3 * (M_PI / 2))
		|| (mlx->ray->flag == 1 && mlx->ray->ray_ngl > 0
			&& mlx->ray->ray_ngl < M_PI))
		offset = texture->width - offset - 1;
	return (offset);
}

void	draw_wall(t_cub *mlx, int t_pix, int b_pix, double wall_h)
{
	mlx_texture_t	*texture;
	uint32_t		*arr;
	double			factor;
	double			x_offset;
	double			y_offset;

	texture = get_texture(mlx, mlx->ray->flag);
	arr = (uint32_t *)texture->pixels;
	factor = (double)texture->height / wall_h;
	x_offset = get_texture_offset(texture, mlx);
	y_offset = (t_pix - (S_H / 2) + (wall_h / 2)) * factor;
	if (y_offset < 0)
		y_offset = 0;
	while (t_pix < b_pix)
	{
		my_mlx_pixel_put(mlx, mlx->ray->index, t_pix, reverse_bytes(
				arr[(int)y_offset * texture->width + (int)x_offset]));
		y_offset += factor;
		t_pix++;
	}
}

void	render_wall(t_cub *mlx, int ray)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	mlx->ray->distance *= cos(nor_angle(mlx->ray->ray_ngl
				- mlx->ply->angle));
	if (mlx->ray->distance < 0.1)
		mlx->ray->distance = 0.1;
	wall_h = (TILE_SIZE / mlx->ray->distance)
		* ((S_W / 2) / tan(mlx->ply->fov_rd / 2));
	b_pix = (S_H / 2) + (wall_h / 2);
	t_pix = (S_H / 2) - (wall_h / 2);
	if (b_pix > S_H)
		b_pix = S_H;
	if (t_pix < 0)
		t_pix = 0;
	mlx->ray->index = ray;
	draw_wall(mlx, t_pix, b_pix, wall_h);
	draw_floor_ceiling(mlx, ray, t_pix, b_pix);
}
