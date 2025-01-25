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

void	my_mlx_pixel_put(t_cub *mlx, int x, int y, int color)	// put the pixel
{
	if (x < 0) // check the x position
		return ;
	else if (x >= S_W)
		return ;
	if (y < 0) // check the y position
		return ;
	else if (y >= S_H)
		return ;
	mlx_put_pixel(mlx->img, x, y, color); // put the pixel
}

float	nor_angle(float angle)	// normalize the angle
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

void	draw_floor_ceiling(t_cub *mlx, int ray, int t_pix, int b_pix)	// draw the floor and the ceiling
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
		my_mlx_pixel_put(mlx, ray, i++, floor_color); // floor
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(mlx, ray, i++, ceiling_color); // ceiling
}

int	get_texture_color(mlx_texture_t *texture, int x, int y)
{
	int color;
	int bpp = 4; // bytes per pixel

	color = *(int *)(texture->pixels + (y * texture->width + x) * bpp);
	return color;
}

int	get_texture(t_cub *mlx, int x, int y)	// get the color of the wall
{
	mlx->ray->ray_ngl = nor_angle(mlx->ray->ray_ngl); // normalize the angle
	if (mlx->ray->flag == 0)
	{
		if (mlx->ray->ray_ngl > M_PI / 2 && mlx->ray->ray_ngl < 3 * (M_PI / 2))
			return get_texture_color(mlx->config.we_texture, x, y); // west wall
		else
			return get_texture_color(mlx->config.ea_texture, x, y); // east wall
	}
	else
	{
		if (mlx->ray->ray_ngl > 0 && mlx->ray->ray_ngl < M_PI)
			return get_texture_color(mlx->config.so_texture, x, y); // south wall
		else
			return get_texture_color(mlx->config.no_texture, x, y); // north wall
	}
}

void	draw_wall(t_cub *mlx, int ray, int t_pix, int b_pix)	// draw the wall
{
	int color;
	int y;
	int	texture_x;
	int	texture_y;
	double	wall_height = b_pix - t_pix;
	double texture_step = (double)mlx->config.no_texture->height / wall_height;
	double texture_pos = 0.0;

	y = t_pix;
	while (y < b_pix)
	{
		texture_x = (int)(ray % mlx->config.no_texture->width);
		texture_y = (int)texture_pos;
		color = get_texture(mlx, texture_x, texture_y);
		my_mlx_pixel_put(mlx, ray, y++, color);
		texture_pos += texture_step;
	}
}

void	render_wall(t_cub *mlx, int ray)	// render the wall
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	mlx->ray->distance *= cos(nor_angle(mlx->ray->ray_ngl - mlx->ply->angle)); // fix the fisheye
	wall_h = (TILE_SIZE / mlx->ray->distance) * ((S_W / 2) / tan(mlx->ply->fov_rd / 2)); // get the wall height
	b_pix = (S_H / 2) + (wall_h / 2); // get the bottom pixel
	t_pix = (S_H / 2) - (wall_h / 2); // get the top pixel
	if (b_pix > S_H) // check the bottom pixel
		b_pix = S_H;
	if (t_pix < 0) // check the top pixel
		t_pix = 0;
	draw_wall(mlx, ray, t_pix, b_pix); // draw the wall
	draw_floor_ceiling(mlx, ray, t_pix, b_pix); // draw the floor and the ceiling
}
