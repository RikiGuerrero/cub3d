/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderUtils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjimenez <pjimenez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:04:32 by pjimenez          #+#    #+#             */
/*   Updated: 2025/01/28 13:06:28 by pjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	reverse_bytes(unsigned int color)
{
	return (((color & 0xFF000000) >> 24)
		| ((color & 0x00FF0000) >> 8)
		| ((color & 0x0000FF00) << 8)
		| ((color & 0x000000FF) << 24));
}

void	my_mlx_pixel_put(t_cub *mlx, int x, int y, int color)
{
	if (x < 0 || x >= S_W || y < 0 || y >= S_H)
		return ;
	mlx_put_pixel(mlx->img, x, y, color);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a << 0);
}
