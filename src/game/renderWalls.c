/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderWalls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguerrer <rguerrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:28:04 by pjimenez          #+#    #+#             */
/*   Updated: 2025/01/14 12:11:14 by rguerrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int reverse_bytes(unsigned int color)
{
	return ((color & 0xFF000000) >> 24) |
			((color & 0x00FF0000) >> 8)  |
			((color & 0x0000FF00) << 8)  |
			((color & 0x000000FF) << 24); 
}

void	my_mlx_pixel_put(t_cub *mlx, int x, int y, int color)
{
	if (x < 0 || x >= S_W || y < 0 || y >= S_H) // Verifica límites
		return;
	mlx_put_pixel(mlx->img, x, y, color); // Coloca el píxel
}

float	nor_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a << 0);
}

void	draw_floor_ceiling(t_cub *mlx, int ray, int t_pix, int b_pix)
{
	int		i;
	int		floor_color;
	int		ceiling_color;

	floor_color = get_rgba(mlx->config.floor_color[0], mlx->config.floor_color[1], \
		mlx->config.floor_color[2], 255);
	ceiling_color = get_rgba(mlx->config.ceiling_color[0], mlx->config.ceiling_color[1], \
		mlx->config.ceiling_color[2], 255);

	i = b_pix;
	while (i < S_H)
		my_mlx_pixel_put(mlx, ray, i++, floor_color);
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(mlx, ray, i++, ceiling_color);
}


mlx_texture_t	*get_texture(t_cub *mlx, int flag)	// Obtiene la textura adecuada según el ángulo
{
	mlx->ray->ray_ngl = nor_angle(mlx->ray->ray_ngl); // normaliza el ángulo
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

double get_texture_offset(mlx_texture_t *texture, t_cub *mlx) // Calcula el desplacamiento de la textura en el eje x
{
	if (mlx->ray->flag == 1)
		return (fmod(mlx->ray->hor_x, TILE_SIZE) * (texture->width / TILE_SIZE));
	else
		return (fmod(mlx->ray->ver_y, TILE_SIZE) * (texture->width / TILE_SIZE));
}

void	draw_wall(t_cub *mlx, int t_pix, int b_pix, double wall_h)
{
	mlx_texture_t	*texture = get_texture(mlx, mlx->ray->flag);
	uint32_t		*arr = (uint32_t *)texture->pixels;
	double			factor = (double)texture->height / wall_h;
	double			x_offset = get_texture_offset(texture, mlx);
	double			y_offset = (t_pix - (S_H / 2) + (wall_h / 2)) * factor;

	if (y_offset < 0) // Asegúrate de no salir del límite
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

	mlx->ray->distance *= cos(nor_angle(mlx->ray->ray_ngl - mlx->ply->angle)); // arreglo de fisheye
	wall_h = (TILE_SIZE / mlx->ray->distance) * ((S_W / 2) / tan(mlx->ply->fov_rd / 2));
	b_pix = (S_H / 2) + (wall_h / 2);
	t_pix = (S_H / 2) - (wall_h / 2);
	if (b_pix > S_H)
		b_pix = S_H;
	if (t_pix < 0)
		t_pix = 0;
	mlx->ray->index = ray; // fija el índice del rayo
	draw_wall(mlx, t_pix, b_pix, wall_h);
	draw_floor_ceiling(mlx, ray, t_pix, b_pix);
}
